#version 460

out vec4 FragColor;
in vec2 TexCoord;
in vec2 OverlayTexCoord;
in vec2 TemplateTexCoord;

uniform sampler2D uTex;
uniform sampler2D templateTex;
uniform sampler2D overlay;
uniform vec3 spriteColor;

void main() {
	vec4 tmp = texture(templateTex, TemplateTexCoord);
	vec4 overlay = texture(overlay, OverlayTexCoord);
	
	
	
	if (overlay.a != 0.0) {
		FragColor = overlay * vec4(spriteColor, 0.0);
	} else {
		if (tmp.x == 1.0 && tmp.y == 1.0 && tmp.z == 1.0) {
			discard;
		}
		if (tmp.x == 0.0 && tmp.y == 0.0 && tmp.z == 0.0 && tmp.w == 1.0)
		{
			FragColor = vec4(0.0, 0.0, 0.0, 1.0);
		}
		else
		FragColor = texture(uTex, TexCoord) * vec4(spriteColor, 1.0);
	}
	
}