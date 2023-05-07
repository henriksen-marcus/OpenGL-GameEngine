#include "MeshComponent.h"
#include <qcolor.h>
#include <sstream>
#include <filesystem>
#include "Math.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Texture3D.h"
#include "World.h"
#include "Source/Game/Arrow.h"
#include "Source/Engine/Timer.h"
#include "Source/Engine/OBJMaterial.h"
#include "Texture.h"


MeshComponent::MeshComponent(Actor* parent, GLenum drawMode)
    : SceneComponent(parent), mShaderName("god"), mTexture(nullptr), mDrawMode(drawMode)
{
    mTimer = new Timer();
}

MeshComponent::~MeshComponent()
{
    delete mTexture;
}

void MeshComponent::LoadMesh(const std::string& path)
{

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<QVector3D> temp_vertices;
	std::vector<QVector2D> temp_uvs;
	std::vector<QVector3D> temp_normals;

	FILE* file = fopen(path.c_str(), "r");
	if (!file) {
	    qDebug() << "Impossible to open the file!";
	    return;
	}

    while(true) 
    {
	    char lineHeader[128];
	    // Read the first word of the line
	    int res = fscanf(file, "%s", lineHeader);
	    if (res == EOF) break; // EOF = End Of File. Quit the loop.

	    if (strcmp(lineHeader, "v") == 0) // Vertex position
        {
		    QVector3D vertex;
		    fscanf_s(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
		    temp_vertices.push_back(vertex);
        }
        else if (strcmp( lineHeader, "vt" ) == 0) // Vertex texture coordinate
        {
		    QVector2D uv;
		    fscanf_s(file, "%f %f\n", &uv[0], &uv[1]);
		    temp_uvs.push_back(uv);
        }
        else if (strcmp( lineHeader, "vn" ) == 0) // Vertex normal
        {
		    QVector3D normal;
		    fscanf_s(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
		    temp_normals.push_back(normal);
        }
        else if (strcmp( lineHeader, "f" ) == 0)
        {
		    std::string vertex1, vertex2, vertex3;
		    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    if (matches != 9){
		        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
		        return;
		    }
		    vertexIndices.push_back(vertexIndex[0]);
		    vertexIndices.push_back(vertexIndex[1]);
		    vertexIndices.push_back(vertexIndex[2]);
		    uvIndices    .push_back(uvIndex[0]);
		    uvIndices    .push_back(uvIndex[1]);
		    uvIndices    .push_back(uvIndex[2]);
		    normalIndices.push_back(normalIndex[0]);
		    normalIndices.push_back(normalIndex[1]);
		    normalIndices.push_back(normalIndex[2]);
        }
    }

    mIndices = vertexIndices;
    for (int i = 0; i < vertexIndices.size(); i++)
    {
        mVertices.emplace_back(temp_vertices[vertexIndices[i] - 1], QVector3D(1.f, 1.f, 1.f), temp_uvs[uvIndices[i] - 1], temp_normals[normalIndices[i] - 1]);
	}
}

void MeshComponent::LoadFromOBJ(const std::string& path)
{
    mVertices.clear();
    mIndices.clear();

    std::vector<QVector3D> OBJ_vertices, OBJ_normals;
	std::vector<QVector2D> OBJ_texcoords;

    std::vector<GLint> OBJ_normal_indices, OBJ_texcoord_indices;

    std::vector<OBJMaterial*> OBJ_materials;
    std::unordered_map<int, OBJMaterial*> indexMaterial;

    OBJMaterial* current_material = nullptr;

    std::stringstream ss;
    std::ifstream in_obj_file(path);
    std::string line = "";
    std::string prefix = "";
    QVector3D temp_vec3;
    QVector2D temp_vec2;

    if (!in_obj_file.is_open())
    {
    	qDebug() << "MESHCOMPONENT::OBJLOADER::Failed to open file: " << path.c_str();
		return;
	}

    // Read the file line by line
    while (std::getline(in_obj_file, line))
    {
        // Get the prefix of the line
    	ss.clear();
		ss.str(line);
		
		ss >> prefix;
        if (prefix == "mtllib") // One obj file can have multiple mtl files attached
        {
            // Get file name
	        std::string material_file;
			ss >> material_file;

            // Add given obj path to the mtl file path
            std::string mtl_path = std::filesystem::path(path).parent_path().string();
            mtl_path += "/" + material_file;

            // Retrieve the containing materials
            auto mtl = ParseMTL(mtl_path);
            OBJ_materials.insert(OBJ_materials.end(), mtl.begin(), mtl.end());
		}
		else if (prefix == "v") // Vertex position
		{
            // Load all the vertices in order
			ss >> temp_vec3[0] >> temp_vec3[1] >> temp_vec3[2];
            OBJ_vertices.push_back(temp_vec3);
			mVertices.emplace_back(temp_vec3);
		}
        else if (prefix == "vt") // Vertex texture coordinate
        {
        	// Load all the texture coordinates in order
			ss >> temp_vec2[0] >> temp_vec2[1];
			OBJ_texcoords.push_back(temp_vec2);
        }
		else if (prefix == "vn") // Vertex normal
		{
            // Load all the normals in order
			ss >> temp_vec3[0] >> temp_vec3[1] >> temp_vec3[2];
			OBJ_normals.push_back(temp_vec3.normalized());
		}
        else if (prefix == "s")
        {
	        std::string smooth;
            ss >> smooth;
            bSmoothShading = smooth == "1";
        }
        else if (prefix == "usemtl")
		{
			std::string material_name;
			ss >> material_name;

			for (const auto& mat : OBJ_materials)
				if (mat->mName == material_name)
				{
					current_material = mat;
					break;
				}
        }
		else if (prefix == "f") // Face
		{
			GLint v_index, vt_index, vn_index;
			char delimiter;
			std::string vertex_str;
			while (std::getline(ss, vertex_str, ' '))
			{
				if (vertex_str.empty())
					continue;

				std::stringstream vertex_ss(vertex_str);
				vertex_ss >> v_index >> std::noskipws >> delimiter >> std::noskipws >> vt_index >> std::noskipws >>
					delimiter >> std::noskipws >> vn_index;

				mIndices.push_back(v_index - 1);
				OBJ_texcoord_indices.push_back(vt_index - 1);
				OBJ_normal_indices.push_back(vn_index - 1);

                mVertices[v_index- 1].SetUV(OBJ_texcoords[vt_index - 1]);
                mVertices[v_index - 1].SetNormal(OBJ_normals[vn_index - 1].normalized());

                if (current_material) 
                {
                	mVertices[v_index - 1].SetColor(current_material->mDiffuse);
                    indexMaterial[v_index - 1] = current_material;
                }
				else mVertices[v_index - 1].SetColor(QVector3D(1.f, 1.f, 1.f));

                //qDebug() << v_index << "/" << vt_index << "/" << vn_index;
			}
		}
	}

    // Load duplicate vertices for hard shading
    if (!bSmoothShading)
    {
	    mVertices.clear();

        for (size_t i = 0; i < mIndices.size(); ++i)
        {
	        Vertex v;
			v.SetPos(OBJ_vertices[mIndices[i]]);
			v.SetUV(OBJ_texcoords[OBJ_texcoord_indices[i]]);
			v.SetNormal(OBJ_normals[OBJ_normal_indices[i]]);

	        /*auto it = indexMaterial.find(i);
	        if (it != indexMaterial.end()) 
                v.SetColor(it->second->mDiffuse);
			else 
                v.SetColor(QVector3D(1.f, 1.f, 1.f));*/

			mVertices.push_back(v);
		}

        for (auto& i : indexMaterial)
            mVertices[i.first].SetColor(i.second->mDiffuse);

        std::cout << indexMaterial.size() << " " << mVertices.size() << std::endl;


        mIndices.clear();
    }
}

std::vector<OBJMaterial*> MeshComponent::ParseMTL(const std::string& path)
{
    std::cout << "MESHCOMPONENT::OBJLOADER::Parsing MTL file: '" << path.c_str() << "'";
    std::ifstream in_mtl_file(path);
    if (!in_mtl_file.is_open()) return {};
    std::cout << "MESHCOMPONENT::OBJLOADER::MTL file opened successfully";

    OBJMaterial* current_mat = nullptr;

    std::vector<OBJMaterial*> materials;
    std::string line = "";
    std::string prefix = "";
	std::stringstream ss;
	while (std::getline(in_mtl_file, line))
	{
        // Get the prefix of the line
    	ss.clear();
		ss.str(line);
        ss >> prefix;

        if (prefix == "newmtl")
        {
            if (current_mat) materials.push_back(current_mat);
            std::string name;
            ss >> name;
            current_mat = new OBJMaterial();
            current_mat->mName = name;
        }
        else if (prefix == "Ka")
        {
	        QVector3D ambient;
	        ss >> ambient[0] >> ambient[1] >> ambient[2];
	        current_mat->mAmbient = ambient;
        }
        else if (prefix == "Kd")
        {
	        QVector3D diffuse;
	        ss >> diffuse[0] >> diffuse[1] >> diffuse[2];
	        current_mat->mDiffuse = diffuse;
        }
        else if (prefix == "Ks")
        {
	        QVector3D specular;
	        ss >> specular[0] >> specular[1] >> specular[2];
	        current_mat->mSpecular = specular;
        }
        else if (prefix == "Ke")
        {
	        QVector3D emission;
	        ss >> emission[0] >> emission[1] >> emission[2];
	        current_mat->mEmission = emission;
        }
        else if (prefix == "Ns")
        {
	        float shininess;
	        ss >> shininess;
	        current_mat->mShininess = shininess;
        }
        else if (prefix == "d")
        {
	        float transparency;
	        ss >> transparency;
	        current_mat->mTransparency = transparency;
        }
        else if (prefix == "Ni")
        {
	        float opticalDensity;
	        ss >> opticalDensity;
	        current_mat->mOpticalDensity = opticalDensity;
        }
        else if (prefix == "illum")
        {
	        float illuminationModel;
	        ss >> illuminationModel;
	        current_mat->mIlluminationModel = illuminationModel;
        }
	}

    if (current_mat) materials.push_back(current_mat);
    return materials;
}

void MeshComponent::UpdateMesh()
{
    // Update the vertex data in the VBO
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshComponent::SetTexture2D(Texture2D* texture)
{
    mTexture = texture;
    mTextureDimension = 2;
    Init();
}

void MeshComponent::SetTexture2D(const std::string& path)
{
    mTexture = new Texture2D(path);
    mTextureDimension = 2;
    Init();
}

void MeshComponent::SetTexture3D(Texture3D* texture)
{
    mTexture = texture;
    mTextureDimension = 3;
    Init();
}

void MeshComponent::GenerateNormals()
{
    if (mVertices.empty() || mIndices.empty() || mDrawMode == GL_LINES) return;

    // Reset the normals
    for (int i = 0; i < mVertices.size(); i++)
    {
    	mVertices[i].SetNormal(QVector3D());
	}

    // Loop through each triangle and add the normal
    for (int i = 0; i < mIndices.size(); i += 3)
    {
    	// Get the indices of the three vertices that make up this triangle
		GLuint i1 = mIndices[i];
		GLuint i2 = mIndices[i + 1];
		GLuint i3 = mIndices[i + 2];
		// Get the vertices
		QVector3D v1 = mVertices[i1].GetPos();
		QVector3D v2 = mVertices[i2].GetPos();
		QVector3D v3 = mVertices[i3].GetPos();
		// Calculate the normal
		QVector3D normal = QVector3D::crossProduct(v2 - v1, v3 - v1);
		// Add the normal to the vertices
		mVertices[i1].AddNormal(normal);
		mVertices[i2].AddNormal(normal);
		mVertices[i3].AddNormal(normal);
	}

    // Normalize the normals
    for (int i = 0; i < mVertices.size(); i++)
    {
    	mVertices[i].SetNormal(mVertices[i].GetNormal().normalized());
	}
}

void MeshComponent::GenerateQuadNormals()
{
    if (mVertices.empty() || mIndices.empty() || mDrawMode == GL_LINES) return;
	// Reset the normals
	for (int i = 0; i < mVertices.size(); i++)
	{
		mVertices[i].SetNormal(QVector3D());
	}
	// Loop through each triangle and add the normal
	for (int i = 0; i < mIndices.size(); i += 6)
	{
		// Get the indices of the three vertices that make up this triangle
		GLuint i1 = mIndices[i];
		GLuint i2 = mIndices[i + 1];
		GLuint i3 = mIndices[i + 2];
		GLuint i4 = mIndices[i + 3];
		GLuint i5 = mIndices[i + 4];
		GLuint i6 = mIndices[i + 5];
		// Get the vertices
		QVector3D v1 = mVertices[i1].GetPos();
		QVector3D v2 = mVertices[i2].GetPos();
		QVector3D v3 = mVertices[i3].GetPos();
		QVector3D v4 = mVertices[i4].GetPos();
		QVector3D v5 = mVertices[i5].GetPos();
		QVector3D v6 = mVertices[i6].GetPos();
		// Calculate the normal
		QVector3D normal1 = QVector3D::crossProduct(v2 - v1, v3 - v1);
		QVector3D normal2 = QVector3D::crossProduct(v5 - v4, v6 - v4);
        QVector3D normal3 = (normal1 + normal2);
		// Add the normal to the vertices
		mVertices[i1].AddNormal(normal3);
		mVertices[i2].AddNormal(normal3);
		mVertices[i3].AddNormal(normal3);
		mVertices[i4].AddNormal(normal3);
		mVertices[i5].AddNormal(normal3);
		mVertices[i6].AddNormal(normal3);
	}
	// Normalize the normals
	for (int i = 0; i < mVertices.size(); i++)
	{
		mVertices[i].SetNormal(mVertices[i].GetNormal().normalized());
	}
}

void MeshComponent::GenerateNeighbors()
{
    // For each triangle
    for (int i = 0; i < mIndices.size(); i+=3)
    {
        int neighborsAdded = 0;
        // Check every triangle against every triangle
	    for (int k = 0; k < mIndices.size(); k+= 3)
	    {
            // Don't compare the triangle to itself
            if (k == i) continue;
            // How many vertices are the same
            int sharedVertices = 0;

            // Compare the indices of this triangle (i) to the other triangle (k)
            for (int j = 0; j < 3; j++)
            {
	            for (int l = 0; l < 3; l++)
	            {
		            if (mIndices[i + j] == mIndices[k + l])
		            {
			            sharedVertices++;
                        break;
		            }
	            }
            }

            // We need to share an edge to be a neighbor, meaning two vertices
            // We add the index of the "index of the first vertex" of the neighboring triangle
            if (neighborsAdded < 3)
            {
	    		if (sharedVertices == 2)
	    		{
                    mNeighbors.push_back(k);
					neighborsAdded++;
	    		}
                //else if (k == mIndices.size() - 1) mNeighbors.push_back(-1);
            }
	    	else break;
	    }
        if (neighborsAdded == 1) 
        {
        	mNeighbors.push_back(-1);
        	mNeighbors.push_back(-1);
        }
        else if (neighborsAdded == 2) 
        {
            mNeighbors.push_back(-1);
        }
    }

    cPrint("Indices size: " + std::to_string(mIndices.size()) + " Neighbour size: " + std::to_string(mNeighbors.size()));
    //for (int i = 0; i < mIndices.size(); i++)
    //	cPrint(std::to_string(mIndices[i]));

    //cPrint("______");

    //for (int i = 0; i < mNeighbors.size(); i++)
    //    cPrint(std::to_string(mNeighbors[i]));

    //return;
    cPrint("Indices: Neighbors:\n");
    for (int i = 0; i < mIndices.size(); i+=3)
    {
    	cPrint(std::to_string(mIndices[i]) + " " + std::to_string(mIndices[i+1]) + " " + std::to_string(mIndices[i+2]) + "   " + std::to_string(mNeighbors[i]) + " " + std::to_string(mNeighbors[i+1]) + " " + std::to_string(mNeighbors[i+2]));
	}


    QVector3D b = mVertices[mIndices[0]].GetPos();
    b.setX(b.y() + 1.f);
    b/=3.f;
    auto a = new Arrow(b, 1, QVector3D(0.f, 1.f, 0.f));
    auto w = GetWorld();
    if (w)
    {
		GetWorld()->mRenderer->Add("arrow", a);
    }
}

float MeshComponent::GetHeight(const QVector2D& point)
{
    if (mVertices.empty() || mIndices.empty() || mDrawMode == GL_LINES) return -1;
    mTimer->Start();
    // For each triangle
    for (int i = std::max(0, triangleIndex - 10); i < mIndices.size(); i += 3)
    {
	    // Get the indices of the three vertices that make up this triangle
	    GLuint i1 = mIndices[i];
	    GLuint i2 = mIndices[i + 1];
	    GLuint i3 = mIndices[i + 2];

	    // Get the vertices
	    auto v1 = mVertices[i1].GetPos2D();
	    auto v2 = mVertices[i2].GetPos2D();
	    auto v3 = mVertices[i3].GetPos2D();

	    // Get the barycentric coordinates
        float u, v, w;
        Math::Barycentric(v1, v2, v3, point, u, v, w);

	    // Check if the point is inside the triangle
        if (u >= 0.f && u <= 1.f && v >= 0.f && v <= 1.f && w >= 0.f && w <= 1.f)
		{
			// Get the height of the triangle
			auto h = mVertices[i1].y * u + mVertices[i2].y * v + mVertices[i3].y * w;
            //print("baryc timer: " + mTimer->GetDurationAsString());
            return h;
		}
    }
    return -1;
}

unsigned MeshComponent::GetMeshHeight()
{
    return std::sqrt(mIndices.size()/3);
}

unsigned MeshComponent::GetMeshWidth()
{
    return 0;
}

void MeshComponent::ClearMemory()
{
    mVertices.clear();
    mIndices.clear();
}

void MeshComponent::Init()
{
    if (mVertices.empty()) return;

    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    // [x,y,z,r,g,b,u,v,a,m,c]
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    if (mTexture != nullptr)
    {
        // Texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }

    // Normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
    

    if (!mIndices.empty())
    {
        glGenBuffers(1, &mIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void MeshComponent::Draw()
{
    if (mVertices.empty()) return;

    if (mTexture) mTexture->Bind();

	UseShader(mShaderName);

    // Uniforms specific to the shader.
    Shader* activeShader = GetActiveShader();
    activeShader->SendUniforms();

    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    activeShader->SetBool("useLighting", bUseLighting);
    //activeShader->SetInt("textureDimension", mTextureDimension);

    glBindVertexArray(mVAO);

    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(mDrawMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    glBindVertexArray(0);
    activeShader->SetBool("useLighting", false);
    if (mTexture) mTexture->Unbind();
}
