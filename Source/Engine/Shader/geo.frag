#version 410 core

in vec4 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;


uniform sampler2D texture_IN;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform bool useLighting;

out vec4 fragmentColor;

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
		float ambientIntensity = 0.1f;
		vec4 ambientColor = vec4(lightColor, 1.f) * ambientIntensity;

		vec3 lightDirection = normalize(lightPosition - gl_FragCoord.xyz);
		float diffuseFactor = max(dot(normalize(fragNormal), lightDirection), 0.f);
		float diffuseIntensity = 0.8f;
		vec4 diffuseColor = vec4(lightColor, 1.f) * diffuseIntensity * diffuseFactor;
		fragmentColor = vec4(texColor.rgb * fragColor.rgb * (ambientColor + diffuseColor).rgb, texColor.a);
		
//		float lightFactor = max(dot(normalize(fragNormal - 0.5), lightDirection), 0.f);
//		fragmentColor = vec4(texColor.rgb * fragColor.rgb * lightFactor, texColor.a);
	}
	else 
	{
		fragmentColor = vec4(texColor.rgb * fragColor.rgb, texColor.a);
	}
}