attribute	highp	vec3	aPos ;		// ���W( ���[�J����� )
attribute	mediump	vec4	aDif ;			// �f�B�t���[�Y�J���[

#if USE_TEXCOORD0 != 0 || USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
attribute	mediump	vec2	aTexUV0 ;		// �e�N�X�`�����W�O
#endif // USE_TEXCOORD0 != 0 || USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0

#if USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
attribute	mediump	vec2	aTexUV1 ;		// �e�N�X�`�����W�P
#endif // USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0


// ���_�V�F�[�_�[�̏o��
varying		mediump	vec4	vDif ;			// �f�B�t���[�Y�J���[
varying		mediump	vec2	vTexUV0 ;		// �e�N�X�`�����W�O
varying		mediump	vec2	vTexUV1 ;		// �e�N�X�`�����W�P


uniform		highp	vec4	uLWMat[ 3 ] ;		// ���[�J���@���@���[���h�s��
uniform		highp	vec4	uViewMat[ 3 ] ;		// ���[���h�@���@�r���[�s��
uniform		highp	vec4	uProjMat[ 4 ] ;		// �r���[�@���@�v���W�F�N�V�����s��

uniform		mediump	vec4	uTexMat[ 6 /* [ DX_VS_CONSTF_TEXTURE_MATRIX_NUM ][ 2 ] */ ] ;	// �e�N�X�`�����W����p�s��

// 3D�p
void main( void )
{
	highp	vec4    lLocalPos ;
	highp	vec4    lWorldPos ;
	highp	vec4    lViewPos ;
	mediump	vec4    lTexUVTemp ;


	// ���[�J�����W�̏���
	lLocalPos.xyz   = aPos ;
	lLocalPos.w     = 1.0 ;


	// ���W�ϊ�
	lWorldPos.x     = dot( lLocalPos, uLWMat[ 0 ] ) ;
	lWorldPos.y     = dot( lLocalPos, uLWMat[ 1 ] ) ;
	lWorldPos.z     = dot( lLocalPos, uLWMat[ 2 ] ) ;
	lWorldPos.w     = 1.0;
	
	lViewPos.x      = dot( lWorldPos, uViewMat[ 0 ] ) ;
	lViewPos.y      = dot( lWorldPos, uViewMat[ 1 ] ) ;
	lViewPos.z      = dot( lWorldPos, uViewMat[ 2 ] ) ;
	lViewPos.w      = 1.0;
	
	gl_Position.x = dot( lViewPos, uProjMat[ 0 ] ) ;
	gl_Position.y = dot( lViewPos, uProjMat[ 1 ] ) ;
	gl_Position.z = dot( lViewPos, uProjMat[ 2 ] ) ;
	gl_Position.w = dot( lViewPos, uProjMat[ 3 ] ) ;


	// �p�����[�^�Z�b�g
	vDif    = aDif ;

	lTexUVTemp.z = 1.0 ;
	lTexUVTemp.w = 1.0 ;
#if USE_TEXCOORD0 != 0 || USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
	lTexUVTemp.xy = aTexUV0 ;
	vTexUV0.x = dot( lTexUVTemp, uTexMat[ 0 ] ) ;
	vTexUV0.y = dot( lTexUVTemp, uTexMat[ 1 ] ) ;
#else  // USE_TEXCOORD0 != 0 || USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
	vTexUV0.x = 0.0 ;
	vTexUV0.y = 0.0 ;
#endif // USE_TEXCOORD0 != 0 || USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0

#if USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
	lTexUVTemp.xy = aTexUV1 ;
	vTexUV1.x = dot( lTexUVTemp, uTexMat[ 0 ] ) ;
	vTexUV1.y = dot( lTexUVTemp, uTexMat[ 1 ] ) ;
#else  // USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
	vTexUV1.x = 0.0 ;
	vTexUV1.y = 0.0 ;
#endif // USE_VERTEX3DSHADER != 0 || USE_VERTEX3D != 0
}
