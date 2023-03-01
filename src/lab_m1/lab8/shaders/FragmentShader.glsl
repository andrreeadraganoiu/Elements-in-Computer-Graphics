#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;


uniform vec3 light_direction2;
uniform vec3 light_position2;


// TODO(student): Declare any other uniforms

uniform vec3 object_color;

uniform int isSpot;
uniform float angle;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
	vec3 L = normalize( light_position - world_position );
	vec3 V = normalize( eye_position - world_position );
	vec3 H = normalize( L + V );
	vec3 R = reflect( L, world_normal );
    

	vec3 L2 = normalize( light_position2 - world_position );
	vec3 V2 = normalize( eye_position - world_position );
	vec3 H2 = normalize( L + V );
	vec3 R2 = reflect( L, world_normal );
	
	// TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = material_kd * 0.25;
    float diffuse_light = material_kd * max(dot(L, world_normal), 0);
    float specular_light = material_ks * pow(max(dot(R, V), 0), material_shininess);
    

	float ambient_light2 = material_kd * 0.25;
    float diffuse_light2 = material_kd * max(dot(L2, world_normal), 0);
    float specular_light2 = material_ks * pow(max(dot(R2, V2), 0), material_shininess);
	
	// It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    
	if (diffuse_light > 0)
    {
    }

    
	// TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
	float cut_off = angle;
	float spot_light = dot(-L, light_direction);
	float spot_light2 = dot(-L2, light_direction2);
	float spot_light_limit = cos(cut_off); 
	// Quadratic attenuation
	float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
	float linear_att2 = (spot_light2 - spot_light_limit) / (1 - spot_light_limit);
	
	float light_att_factor = pow(linear_att, 2);
	float light_att_factor2 = pow(linear_att2, 2);

	float aten_fac = 1 / pow(length(light_position - world_position), 2);
	float aten_fac2 = 1 / pow(length(light_position2 - world_position), 2);
	vec3 light;
	vec3 light2;
	
	if (isSpot == 0) {
		light = object_color * (ambient_light + aten_fac * (diffuse_light + specular_light));
		light2 = object_color * (ambient_light2 + aten_fac2 * (diffuse_light2 + specular_light2));
		light = light + light2;
	} else {

		if (spot_light > cos(cut_off))
		{
			// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
			// se calculeaza atenuarea luminii
			
			light = object_color * (ambient_light + (light_att_factor + aten_fac) * (diffuse_light + specular_light));
			light2 = object_color * (ambient_light2 + (light_att_factor2 + aten_fac2) * (diffuse_light2 + specular_light2));
			light = light + light2;
		} else {
			light = ambient_light * object_color;
			light2 = ambient_light2 * object_color;
			light = light + light2;
		}
	}

    
	// TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    
	// TODO(student): Write pixel out color
	out_color = vec4(light, 1);
}
