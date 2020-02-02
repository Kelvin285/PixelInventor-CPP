#version 460
layout (location=0) in vec4 vertex;

out vec2 TexCoord;
out vec2 OverlayTexCoord;
out vec2 TemplateTexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 uv;
uniform vec4 overlayUv;
uniform vec4 tempUv;

void main()
{

	vec2 tc = vec2(vertex.z * uv.z + uv.x, vertex.w * uv.w + uv.y);
	vec2 otc = vec2(vertex.z * overlayUv.z + overlayUv.x, vertex.w * overlayUv.w + overlayUv.y);
	vec2 tuv = vec2(vertex.z * tempUv.z + tempUv.x, vertex.w * tempUv.w + tempUv.y);

	TexCoord = tc;
	OverlayTexCoord = otc;
	TemplateTexCoord = tuv;
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}