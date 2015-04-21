#version 410

in vec2 frag_texcoord;
in vec3 vNormal;
in vec3 vPosition;

out vec4 out_color;
uniform sampler2D box_texture;
uniform sampler2D grass_texture;
uniform sampler2D rock_texture;
uniform sampler2D dirt_texture;
//Fun stuff
//Light stuff

uniform vec3 LightDir;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform float SpecPow;
uniform vec3 AmbientIntestity;
uniform vec3 Light;

float WaterLevel;

void main()
  {

    vec3 ambient = LightColour * AmbientIntestity;
    float d = max(0,
    dot(normalize(vNormal.xyz),LightDir ) );
    vec3 E = normalize( CameraPos - vPosition.xyz );
    vec3 R = reflect( -LightDir, vNormal.xyz );
    float s = max( 0, dot( E, R ) );
    s = pow( s, SpecPow );
    out_color = texture(grass_texture, frag_texcoord) *vec4( LightColour * d +
    LightColour * ambient, 1);

  }
