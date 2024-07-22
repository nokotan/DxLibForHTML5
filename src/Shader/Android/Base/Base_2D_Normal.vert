attribute	highp	vec4	aPosF4 ;

#ifdef USE_DIFFUSE
attribute	lowp	vec4	aDif ;			// �f�B�t���[�Y�J���[
#endif // USE_DIFFUSE

#ifdef USE_TEXCOORD0
attribute	mediump	vec2	aTexUV0 ;		// �e�N�X�`�����W�O
#endif // USE_TEXCOORD0

#ifdef USE_TEXCOORD1
attribute	mediump	vec2	aTexUV1 ;		// �e�N�X�`�����W�P
#endif // USE_TEXCOORD1

uniform		highp	vec4	uAntiVPMat[ 4 ] ;

varying		lowp	vec4	vDif ;
varying		mediump	vec2	vTexUV0 ;
varying		mediump	vec2	vTexUV1 ;

// 2D�p
void main( void )
{
	highp vec4 lPos ;
	highp vec4 lAVPos ;
	
	// �p�����[�^�Z�b�g
#ifdef USE_DIFFUSE
	vDif = aDif ;
#else  // USE_DIFFUSE
	vDif = 1.0 ;
#endif // USE_DIFFUSE

#ifdef USE_TEXCOORD0
	vTexUV0 = aTexUV0 ;
#else  // USE_TEXCOORD0
	vTexUV0.x = 0.0 ;
	vTexUV0.y = 0.0 ;
#endif // USE_TEXCOORD0

#ifdef USE_TEXCOORD1
	vTexUV1 = aTexUV1 ;
#else  // USE_TEXCOORD1
	vTexUV1.x = 0.0 ;
	vTexUV1.y = 0.0 ;
#endif // USE_TEXCOORD1

	lPos = aPosF4 ;
	lPos.w = 1.0 / lPos.w ;
	lPos.x *= lPos.w ;
	lPos.y *= lPos.w ;
	lPos.z *= lPos.w ;

	// ���W�ϊ�
	lAVPos.x = dot( lPos, uAntiVPMat[ 0 ] ) ;
	lAVPos.y = dot( lPos, uAntiVPMat[ 1 ] ) ;
	lAVPos.z = dot( lPos, uAntiVPMat[ 2 ] ) ;
	lAVPos.w = dot( lPos, uAntiVPMat[ 3 ] ) ;
	gl_Position = lAVPos ;
}
