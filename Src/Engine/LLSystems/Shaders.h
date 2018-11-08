#pragma once

static const char DEFAULT_VERTEX_SHADER[] =
	"#version 430 core\n\
	in vec2 position;\n\
	void main()\n\
	{\n\
	        gl_Position = vec4(position, 0.0, 1.0);\n\
        }";

static const char WHITE_FRAGMENT_SHADER[] =
	"#version 430 core\n\
        out vec4 outColor;\n\
        void main()\n\
        {\n\
                outColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
        }";
