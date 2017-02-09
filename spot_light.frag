

varying vec4 ambient;

varying vec4 diffuse0, diffuse1, diffuse2; 

varying vec3 normal; 

uniform sampler2D tex; 

varying vec3 lightDir0, lightDir1, lightDir2;

varying vec3 halfVector0, halfVector1, halfVector2;

varying float dist;
  

void main()  
{  
    vec3 n;
	vec3 halfV0, halfV1, halfV2;  
    float NdotL0, NdotL1, NdotL2;
	float NdotHV0, NdotHV1, NdotHV2;

	vec3 ct,cf;  
    vec4 texel;  
	float at,af;
	float spotEffect, att;
	
    vec4 color = ambient;
     
    n = normalize(normal);
      
    NdotL0 = max(dot(n,lightDir0),0.0);
	NdotL1 = max(dot(n,lightDir1),0.0);
	NdotL2 = max(dot(n,lightDir2),0.0);
	//////////////////////////////////////////////////////////////////////////////////////////////
	if (NdotL0 > 0.0)  
	{  
		color += diffuse0 * NdotL0;  
		halfV0 = normalize(halfVector0);  
		NdotHV0 = max(dot(n,halfV0),0.0);

		color += gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV0, gl_FrontMaterial.shininess);  
	}

	if (NdotL1 > 0.0)  
	{  
		color += diffuse1 * NdotL1;  
		halfV1 = normalize(halfVector1);  
		NdotHV1 = max(dot(n,halfV1),0.0);

		color += gl_FrontMaterial.specular * gl_LightSource[1].specular * pow(NdotHV1, gl_FrontMaterial.shininess);  
	}  

	if (NdotL2 > 0.0)  
	{  
		spotEffect = dot(normalize(gl_LightSource[2].spotDirection), normalize(-lightDir2));
		 if (spotEffect > gl_LightSource[2].spotCosCutoff)  
		{ 
			color += gl_FrontMaterial.ambient * gl_LightSource[2].ambient;

			spotEffect = pow(spotEffect, gl_LightSource[2].spotExponent); 
			att = spotEffect / (gl_LightSource[2].constantAttenuation + gl_LightSource[2].linearAttenuation * dist + gl_LightSource[2].quadraticAttenuation * dist * dist);


			color += att * diffuse2 * NdotL2;
			halfV2 = normalize(halfVector2);
			NdotHV2 = max(dot(n,halfV2),0.0);

			color += att * gl_FrontMaterial.specular * gl_LightSource[2].specular * pow(NdotHV2, gl_FrontMaterial.shininess);  
		}
	}
    //////////////////////////////////////////////////////////////////////////////////////////////

	cf = color; 
    af = gl_FrontMaterial.diffuse.a;

	texel = texture2D(tex,gl_TexCoord[0].st);
    ct = texel.rgb;
    at = texel.a;

	gl_FragColor = vec4(ct * cf, at * af); 
}