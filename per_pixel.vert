

varying vec4 ambient;

varying vec4 diffuse0, diffuse1, diffuse2;

varying vec3 normal;

varying vec3 lightDir0, lightDir1, lightDir2;  

varying vec3 halfVector0, halfVector1, halfVector2;


void main()  
{   
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    lightDir0 = normalize(vec3(gl_LightSource[0].position));
	lightDir1 = normalize(vec3(gl_LightSource[1].position));
	lightDir2 = normalize(vec3(gl_LightSource[2].position));
     
    halfVector0 = normalize(gl_LightSource[0].halfVector.xyz);
	halfVector1 = normalize(gl_LightSource[1].halfVector.xyz);
	halfVector2 = normalize(gl_LightSource[2].halfVector.xyz);
    //////////////////////////////////////////////////////////////////////////////////////////////     
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.ambient * gl_LightSource[1].ambient + gl_FrontMaterial.ambient * gl_LightSource[2].ambient;  
    ambient += gl_FrontMaterial.ambient * gl_LightModel.ambient;
    //////////////////////////////////////////////////////////////////////////////////////////////
	diffuse0 = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	diffuse1 = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse; 
	diffuse2 = gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse; 
	//////////////////////////////////////////////////////////////////////////////////////////////
	gl_TexCoord[0] = gl_MultiTexCoord0;

    gl_Position = ftransform();  
}  