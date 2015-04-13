#version 410

in vec2 frag_texcoord;

out vec4 out_color;
uniform sampler2D box_texture;


  void main()
  {
      out_color = texture(box_texture, frag_texcoord);
	  out_color.a = 1;
  }
