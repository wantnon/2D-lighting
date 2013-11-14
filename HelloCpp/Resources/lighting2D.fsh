//********************************************************
//           by yang chao (wantnon)
//           2013-10-20
//			 blog: http://350479720.qzone.qq.com
//********************************************************

#ifdef GL_ES
precision /*mediump*/highp float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform sampler2D texHeightMap;
uniform float step_s;
uniform float step_t;
uniform vec2 light2DInTexSpace;
uniform vec4 diffuseMaterial;
uniform vec4 ambientMaterial;
uniform vec4 diffuseLight;
uniform vec4 ambientLight;

void main() {


    //
    vec4 diffuseML=diffuseMaterial*diffuseLight;
    vec4 ambientML=ambientMaterial*ambientLight;
    
    //
    vec2 ddn=v_texCoord+vec2(0.0,step_t);
	vec2 dright=v_texCoord+vec2(step_s,0.0);
    vec2 dcenter=v_texCoord+vec2(0.0,0.0);
    
    float Hscale=1.0/255.0*4.0;
    
    float Hdn=texture2D(texHeightMap,ddn).r*Hscale;
    float Hrt=texture2D(texHeightMap,dright).r*Hscale;
    float Hc=texture2D(texHeightMap,dcenter).r*Hscale;
    
    vec3 dnVec=normalize(vec3(0.0,step_t,Hdn-Hc));
    vec3 rtVec=normalize(vec3(step_s,0.0,Hrt-Hc));
    
    vec3 norm=normalize(cross(rtVec,dnVec));
    
    vec3 pos=vec3(v_texCoord.x,v_texCoord.y,Hc);
    
    vec3 lightInTexSpace=vec3(light2DInTexSpace.x,light2DInTexSpace.y,0.4);
    
    //diffuse
    vec3 posToLight=normalize(lightInTexSpace-pos);
    float normDotPosToLight=max(0.0,dot(norm,posToLight));
    vec4 diffuse=vec4(normDotPosToLight*vec3(diffuseML),1.0);
    //ambient
    vec4 ambient = ambientML;
    //
    gl_FragColor=texture2D(CC_Texture0,v_texCoord)*vec4(vec3(diffuse+ambient),diffuse.a);
    
}

