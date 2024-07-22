attribute	highp	vec2 aPosF2 ;
attribute	mediump	vec2 aTexUV0 ;		// �e�N�X�`�����W0
attribute	mediump	vec2 aTexUV1 ;		// �e�N�X�`�����W1
attribute	mediump	vec2 aTexUV2 ;		// �e�N�X�`�����W2
attribute	mediump	vec2 aTexUV3 ;		// �e�N�X�`�����W3
attribute	mediump	vec2 aTexUV4 ;		// �e�N�X�`�����W4
attribute	mediump	vec2 aTexUV5 ;		// �e�N�X�`�����W5
attribute	mediump	vec2 aTexUV6 ;		// �e�N�X�`�����W6
attribute	mediump	vec2 aTexUV7 ;		// �e�N�X�`�����W7

varying		mediump	vec2 vTexUV0 ;
varying		mediump	vec2 vTexUV1 ;
varying		mediump	vec2 vTexUV2 ;
varying		mediump	vec2 vTexUV3 ;
varying		mediump	vec2 vTexUV4 ;
varying		mediump	vec2 vTexUV5 ;
varying		mediump	vec2 vTexUV6 ;
varying		mediump	vec2 vTexUV7 ;

// �e�N�X�`�����W8�P���]���p���_�V�F�[�_�[
void main( void )
{
	highp vec4 lPos ;
	
	lPos.x = aPosF2.x ;
	lPos.y = aPosF2.y ;
	lPos.z = 0.0 ;
	lPos.w = 1.0 ;
	
	gl_Position = lPos ;

	vTexUV0 = aTexUV0 ;
	vTexUV1 = aTexUV1 ;
	vTexUV2 = aTexUV2 ;
	vTexUV3 = aTexUV3 ;
	vTexUV4 = aTexUV4 ;
	vTexUV5 = aTexUV5 ;
	vTexUV6 = aTexUV6 ;
	vTexUV7 = aTexUV7 ;
}
