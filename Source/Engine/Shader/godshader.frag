//#version 410 core
//
//in vec4 fragColor;
//out vec4 fragmentColor;
//
//void main()
//{
//    // Color given to current fragment (pixel)
//    fragmentColor = fragColor;
//}									

#version 410 core

in vec4 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPosition;

uniform sampler2D texture_IN;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform bool useLighting;
out vec4 fragmentColor_OUT;
uniform vec3 cameraPosition;

void main()
{
    vec4 texColor = texture2D(texture_IN, fragTexCoord);
    
    if (fragTexCoord == vec2(0.0)) 
	{
        texColor = vec4(1.0, 1.0, 1.0, 1.0); // use white color if sampling from default texture
    }
    
    // Compute lighting if enabled
	if (useLighting)
	{
		// Ambient
		float ambientStrength = 0.1f;
		vec3 ambient = ambientStrength * lightColor;

		// Diffuse
		vec3 norm = normalize(fragNormal);
		vec3 lightDir = normalize(lightPosition - fragPosition);
		float diff = max(dot(norm, lightDir), 0.f);
		vec3 diffuse = diff * lightColor;

		// Specular
		float specularStrength = 0.5f;
		vec3 viewDir = normalize(cameraPosition - fragPosition);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
		vec3 specular = specularStrength * spec * lightColor;

		vec4 result = vec4((ambient + diffuse + specular), 1.f) * fragColor * texColor;
		fragmentColor_OUT = result;
		

//		vec3 lightDirection = normalize(lightPosition - gl_FragCoord.xyz);
//		float diffuseFactor = max(dot(normalize(fragNormal), lightDirection), 0.f);
//		float diffuseIntensity = 0.8f;
//		vec4 diffuseColor = vec4(lightColor, 1.f) * diffuseIntensity * diffuseFactor;
//		fragmentColor = vec4(texColor.rgb * fragColor.rgb * (ambientColor + diffuseColor).rgb, texColor.a);
//		fragmentColor = ambientColor * fragColor;
//		float lightFactor = max(dot(normalize(fragNormal - 0.5), lightDirection), 0.f);
//		fragmentColor = vec4(texColor.rgb * fragColor.rgb * lightFactor, texColor.a);
	}
	else 
	{
		fragmentColor_OUT = vec4(texColor.rgb * fragColor.rgb, texColor.a);
	}
}
