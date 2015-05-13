#version 440

//layout (rgba8) uniform writeonly coherent image3D imageUnit;
layout (r32ui) uniform coherent volatile uimage3D imageUnit;
//layout (rgba8) uniform writeonly coherent volatile image3D imageUnitN;
layout (r32ui) uniform coherent volatile uimage3D imageUnitN;

layout(binding=1, offset=0)  uniform atomic_uint at0;

uniform vec2 WindowSize;
uniform vec4 diffuse;
uniform float shininess;
uniform int texCount;
uniform sampler2D texUnit;


in vec4 worldPos;
in vec4 bBox;
in vec4 colorG;
in vec3 normalG;
in vec2 texCoordG;

out vec4 colorOut;

vec4 convRGBA8ToVec4(uint val)
{
	return vec4(float((val & 0x000000FF)), float((val & 0x0000FF00) >> 8U), float((val & 0x00FF0000) >> 16U), float((val & 0xFF000000) >> 24U));
}

uint convVec4ToRGBA8(vec4 val)
{
	return (uint(val.w) & 0x000000FF) << 24U | (uint(val.z) & 0x000000FF) << 16U | (uint(val.y) & 0x000000FF) << 8U | (uint(val.x) & 0x000000FF);
}

void imageAtomicRGBA8Avg(layout(r32ui) coherent volatile uimage3D grid, ivec3 coords, vec4 value)
{
	value.rgb *= 255.0;
	uint newVal = convVec4ToRGBA8(value);
	uint prevStoredVal = 0;
	uint curStoredVal;

	while((curStoredVal = imageAtomicCompSwap(grid, coords, prevStoredVal, newVal)) != prevStoredVal)
	{
		prevStoredVal = curStoredVal;
		vec4 rval = convRGBA8ToVec4(curStoredVal);
		rval.rgb = (rval.rgb * rval.a);	// Denormalize
		vec4 curValF = rval + value;	// Add
		curValF.rgb /= curValF.a;	// Renormalize
		newVal = convVec4ToRGBA8(curValF);
	}
}

void main() {

	vec4 color;
	if (texCount == 0) 
		color = vec4(diffuse.xyz, 1.0);
	else 
		color = vec4(texture(texUnit, texCoordG).xyz, 1.0);

	vec4 wp = worldPos / worldPos.w;
	int z = int((worldPos.z + 1) * 0.5 * imageSize(imageUnit).z); 
	int y = int((worldPos.y + 1) * 0.5 * imageSize(imageUnit).y); 
	int x = int((worldPos.x + 1) * 0.5 * imageSize(imageUnit).x); 
	
	if (all(greaterThanEqual(-1+2*gl_FragCoord.xy/WindowSize, bBox.xy)) && all(lessThanEqual(-1+2*gl_FragCoord.xy/WindowSize, bBox.zw))){
		imageAtomicRGBA8Avg(imageUnit, ivec3(x,y,z),color);
		//imageStore(imageUnit, ivec3(x,y,z),color);
		imageAtomicRGBA8Avg(imageUnitN, ivec3(x,y,z),vec4(normalG * 0.5 + 0.5,1));
		//imageStore(imageUnitN, ivec3(x,y,z), vec4(normalG * 0.5 + 0.5,shininess));
		atomicCounterIncrement(at0);
	 }
	 else 
		 discard;

	colorOut=color;
}