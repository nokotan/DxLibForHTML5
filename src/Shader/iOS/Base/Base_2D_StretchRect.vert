attribute	highp	vec2	aPosF2 ;
attribute	mediump	vec2	aTexUV0 ;
varying		mediump	vec2	vTexUV0 ;

// �P���]���p���_�V�F�[�_�[
void main( void )
{
	highp vec4 lPos ;
	
	lPos.x = aPosF2.x ;
	lPos.y = aPosF2.y ;
	lPos.z = 0.0 ;
	lPos.w = 1.0 ;
	
	gl_Position = lPos ;

	vTexUV0 = aTexUV0 ;
}
