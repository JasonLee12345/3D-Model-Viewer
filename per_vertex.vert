

varying vec3 lightDir0, lightDir1, lightDir2;

varying vec3 normal;  

varying vec4 color;

void main()  
{  
	float DotL0, DotL1, DotL2;
	float DotLH0, DotLH1, DotLH2;
	vec4  LightAmbient0, LightAmbient1, LightAmbient2;
	vec4  LightDiffuse0, LightDiffuse1, LightDiffuse2; 
	vec4  LightSpecular0, LightSpecular1, LightSpecular2;
	vec4  globalAmbient, sumAmbient, sumDiffuse, sumSpecular;
	
    normal = normalize(gl_NormalMatrix * gl_Normal);  
	//////////////////////////////////////////////////////////////////////////////////////////////
	LightAmbient0 = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	LightAmbient1 = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;
	LightAmbient2 = gl_FrontMaterial.ambient * gl_LightSource[2].ambient;
	globalAmbient = gl_FrontMaterial.ambient * gl_LightModel.ambient;

	sumAmbient = (LightAmbient0 + LightAmbient1 + LightAmbient2) + globalAmbient;
    //////////////////////////////////////////////////////////////////////////////////////////////
    lightDir0 = normalize(vec3(gl_LightSource[0].position));
	lightDir1 = normalize(vec3(gl_LightSource[1].position));
	lightDir2 = normalize(vec3(gl_LightSource[2].position));

	DotL0 = max(dot(normal, lightDir0), 0.0);
	DotL1 = max(dot(normal, lightDir1), 0.0);
	DotL2 = max(dot(normal, lightDir2), 0.0);

	LightDiffuse0 = DotL0 * gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	LightDiffuse1 = DotL1 * gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
	LightDiffuse2 = DotL2 * gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse; 

	sumDiffuse = LightDiffuse0 + LightDiffuse1 + LightDiffuse2;
	//////////////////////////////////////////////////////////////////////////////////////////////
	if(DotL0 > 0.0)
	{
		DotLH0 = max(dot(normal, gl_LightSource[0].halfVector.xyz),0.0);
		LightSpecular0 = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(DotLH0,gl_FrontMaterial.shininess); 
	}

	if(DotL1 > 0.0)
	{
		DotLH1 = max(dot(normal, gl_LightSource[1].halfVector.xyz),0.0);
		LightSpecular1 = gl_FrontMaterial.specular * gl_LightSource[1].specular * pow(DotLH1,gl_FrontMaterial.shininess); 
	}

	if(DotL2 > 0.0)
	{
		DotLH2 = max(dot(normal, gl_LightSource[2].halfVector.xyz),0.0);
		LightSpecular2 = gl_FrontMaterial.specular * gl_LightSource[2].specular * pow(DotLH2,gl_FrontMaterial.shininess); 
	}

	sumSpecular = LightSpecular0 + LightSpecular1 + LightSpecular2;
	//////////////////////////////////////////////////////////////////////////////////////////////
	color = sumAmbient + sumDiffuse+ sumSpecular; // 

    gl_TexCoord[0] = gl_MultiTexCoord0;
  
    gl_Position = ftransform();
}  
