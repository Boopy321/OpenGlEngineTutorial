#version 410

in vec2 frag_texcoord;
in vec3 vNormal;


out vec4 out_color;
uniform sampler2D box_texture;
uniform vec3 Light;

  void main()
  {
    vec3 normal = normalize(vNormal);
    float diffuse= dot(Light,normal);
    out_color = texture(box_texture, frag_texcoord) * diffuse;
	  out_color.a = 1;
  }
