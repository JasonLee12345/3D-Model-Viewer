

varying vec3 lightDir0, lightDir1, lightDir2;;

varying vec3 normal;    

uniform sampler2D tex;  

varying vec4 color;
  
void main()  
{  
    vec3 ct,cf;  
    vec4 texel;  
	float at,af;  
	 
    cf = color; 
    af = gl_FrontMaterial.diffuse.a;
  
    texel = texture2D(tex,gl_TexCoord[0].st);
    ct = texel.rgb;  
    at = texel.a;
  
    gl_FragColor = vec4(ct * cf, at * af); 
	
}  