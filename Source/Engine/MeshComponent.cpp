#include "MeshComponent.h"

#include "Math.h"
#include "Shader.h"
#include "Texture2D.h"
#include "World.h"
#include "Source/Game/Arrow.h"
#include "Source/Engine/Timer.h"


MeshComponent::MeshComponent(Actor* parent, GLenum drawMode)
    : SceneComponent(parent), mShaderName("god"), mTexture(nullptr), mDrawMode(drawMode)
{
    mTimer = new Timer();
}

MeshComponent::~MeshComponent()
{
    delete mTexture;
}

void MeshComponent::SetTexture(Texture2D* texture)
{
    mTexture = texture;
}

void MeshComponent::SetTexture(const std::string& path)
{
    mTexture = new Texture2D(path);
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

    // Print the normals
    /*for (int i = 0; i < mVertices.size(); i++)
    {
    	consolePrint("Vertex " + std::to_string(i) + ": ", mVertices[i].GetNormal());
    }*/
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

    consolePrint("Indices size: " + std::to_string(mIndices.size()) + " Neighbour size: " + std::to_string(mNeighbors.size()));
    //for (int i = 0; i < mIndices.size(); i++)
    //	consolePrint(std::to_string(mIndices[i]));

    //consolePrint("______");

    //for (int i = 0; i < mNeighbors.size(); i++)
    //    consolePrint(std::to_string(mNeighbors[i]));

    //return;
    consolePrint("Indices: Neighbors:\n");
    for (int i = 0; i < mIndices.size(); i+=3)
    {
    	consolePrint(std::to_string(mIndices[i]) + " " + std::to_string(mIndices[i+1]) + " " + std::to_string(mIndices[i+2]) + "   " + std::to_string(mNeighbors[i]) + " " + std::to_string(mNeighbors[i+1]) + " " + std::to_string(mNeighbors[i+2]));
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


// Linear search for now
//float MeshComponent::GetHeight(const QVector2D& point)
//{
//    if (mVertices.empty() || mIndices.empty() || mDrawMode == GL_LINES) return -1;
//
//    // For each triangle
//    for (int i = 0; i < mIndices.size(); i += 3)
//    {
//	    // Get the indices of the three vertices that make up this triangle
//	    GLuint i1 = mIndices[i];
//	    GLuint i2 = mIndices[i + 1];
//	    GLuint i3 = mIndices[i + 2];
//
//	    // Get the vertices
//	    auto v1 = mVertices[i1].GetPos2D();
//	    auto v2 = mVertices[i2].GetPos2D();
//	    auto v3 = mVertices[i3].GetPos2D();
//
//	    // Get the barycentric coordinates
//        float u, v, w;
//        Math::Barycentric(v1, v2, v3, point, u, v, w);
//
//	    // Check if the point is inside the triangle
//        if (u >= 0.f && u <= 1.f && v >= 0.f && v <= 1.f && w >= 0.f && w <= 1.f)
//		{
//			// Get the height of the triangle
//			auto h = mVertices[i1].y * u + mVertices[i2].y * v + mVertices[i3].y * w;
//            return h;
//		}
//    }
//    return -1;
//}

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

    if (bUseLighting) activeShader->SetBool("useLighting", true);

    glBindVertexArray(mVAO);

    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(mDrawMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    activeShader->SetBool("useLighting", false);
    //if (mTexture) mTexture->Unbind();
}
