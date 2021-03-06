#version 330

struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 dir;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec4 position;
    struct {
        float linear;
        float quadratic;
    } att;
};

uniform DirectionalLight directional;
uniform PointLight point;
uniform vec3 WorldEye;
uniform float shininess;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D bumpTexture;
uniform int HasDiffuseTexture;
uniform int HasSpecularTexture;
uniform int HasBumpTexture;

in vec4 WorldPosition;
in vec3 Normal;
in vec2 TexCoord;
in vec4 Color;

out vec4 color;

vec3 getDiffuseColor() {
    if (HasDiffuseTexture == 0) return Color.rgb;

    return vec3(texture(diffuseTexture, TexCoord));
}

vec3 getSpecularColor() {
    if (HasSpecularTexture == 0) return Color.rgb;

    return vec3(texture(specularTexture, TexCoord));
}

vec3 getNormal() {
    vec3 n;
    if (HasBumpTexture == 0) n = normalize(Normal);
    n = normalize(Normal);

    return normalize(n);
}

vec3 calcDirColor(vec3 normal, vec3 matDiffuse, vec3 matSpecular) {
    vec3 R = reflect(-directional.dir, normal);

    vec3 eye = WorldEye;
    eye.y = - eye.y;
    vec3 E = normalize(eye - WorldPosition.xyz);

    float NL = max(dot(-directional.dir, normal), 0);
    float RE = max(dot(E, R), 0);

    vec3 ambient = directional.ambient * matDiffuse;
    vec3 diffuse = directional.diffuse * matDiffuse * NL;
    vec3 specular = directional.specular * matSpecular * pow(RE, shininess);

    return 0.25 * (ambient + diffuse + specular);
}

vec3 calcPointColor(vec3 normal, vec3 matDiffuse, vec3 matSpecular) {
    vec3 pointPosition = point.position.xyz;
    pointPosition.y = -pointPosition.y;

    float dist = length(WorldPosition.xyz - pointPosition);
    vec3 dir = (WorldPosition.xyz - pointPosition) / dist;

    vec3 R = reflect(dir, normal);
    vec3 eye = WorldEye;
    vec3 E = normalize(eye - WorldPosition.xyz);

    float NL = max(dot(-dir, normal), 0);
    float RE = max(dot(E, R), 0);

    vec3 ambient = point.ambient * matDiffuse;
    vec3 diffuse = point.diffuse * matDiffuse * NL;
    vec3 specular = point.specular * matSpecular * pow(RE, 40*shininess);

    vec3 c = ambient + diffuse + specular;

    return c / (1 + point.att.linear * dist + point.att.quadratic * dist * dist);
}

void main() {
    float distanceFromOrigin = length(WorldPosition);
    if (distanceFromOrigin > 10.0) discard;

    vec3 matDiffuse = getDiffuseColor();
    vec3 matSpecular = getSpecularColor();

    vec3 normal = getNormal();
    vec3 total = /*calcDirColor(normal) +*/ calcPointColor(normal, matDiffuse, matSpecular);

    color = vec4(total, 1.0);
}
