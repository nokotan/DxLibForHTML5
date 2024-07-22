attribute	highp	vec3	aPos ;			// ���W( ���[�J����� )
attribute	mediump	vec3	aNrm ;			// �@��
attribute	mediump	vec4	aDif ;			// �f�B�t���[�Y�J���[
attribute	mediump	vec4	aSpc ;			// �X�y�L�����J���[
attribute	mediump	vec2	aTexUV0 ;		// �e�N�X�`�����W�O
attribute	mediump	vec2	aTexUV1 ;		// �e�N�X�`�����W�P

#ifdef BUMPMAP
// �o���v�}�b�v
attribute	mediump	vec3	aTan ;			// �ڐ�( ���[�J����� )
attribute	mediump	vec3	aBin ;			// �]�@��( ���[�J����� )
#endif // BUMPMAP

#ifdef SKINMESH
	// �X�L�j���O���b�V��
	attribute			ivec4	aBlendInd0 ;		// �{�[�������p Float�^�萔�z��C���f�b�N�X�O
	attribute	lowp	vec4	aBlendWeight0 ;		// �{�[�������p�E�G�C�g�l�O

	#ifdef BONE8

		attribute			ivec4	aBlendInd1 ;		// �{�[�������p Float�^�萔�z��C���f�b�N�X�P
		attribute	lowp	vec4	aBlendWeight1 ;		// �{�[�������p�E�G�C�g�l�P

	#endif // BONE8

#endif // SKINMESH

// ���_�V�F�[�_�[�̏o��
varying		mediump	vec4	vDif ;				// �f�B�t���[�Y�J���[
varying		mediump	vec4	vSpc ;				// �X�y�L�����J���[
varying		mediump	vec4	vTexUV0_1 ;			// xy:�e�N�X�`�����W zw:�T�u�e�N�X�`�����W
varying		highp	vec3	vVPos ;				// ���W( �r���[��� )
varying		mediump	vec3	vVNrm ;				// �@��( �r���[��� )
#ifdef BUMPMAP
varying		mediump	vec3	vVTan ;				// �ڐ�( �r���[��� )
varying		mediump	vec3	vVBin ;				// �]�@��( �r���[��� )
#endif // BUMPMAP
varying		highp	vec2	vFog_SM2PosZ ;		// �t�H�O�p�����[�^( x )�ƃV���h�E�}�b�v�R�̃��C�g���W( y )

#if SHADOWMAP != 0
varying		highp	vec4	vSM0Pos_SM2PosX ;	// �V���h�E�}�b�v�P�̃��C�g���W( x, y, z )�ƃV���h�E�}�b�v�R�̃��C�gX���W( w )
varying		highp	vec4	vSM1Pos_SM2PosY ;	// �V���h�E�}�b�v�Q�̃��C�g���W( x, y, z )�ƃV���h�E�}�b�v�R�̃��C�gY���W( w )
#endif // SHADOWMAP


uniform		mediump	vec4	uMatDif ;			// �f�B�t���[�Y�J���[
uniform		mediump	vec4	uMatSpc ;			// �X�y�L�����J���[

// C++ ���Őݒ肷��萔�̒�`
uniform		highp	vec4	uProjMat[ 4 ] ;		// �r���[�@���@�v���W�F�N�V�����s��
uniform		highp	vec4	uViewMat[ 3 ] ;		// ���[���h�@���@�r���[�s��
uniform		highp	vec4	uFog ;				// �t�H�O�p�p�����[�^( x:end/(end - start)  y:-1/(end - start)  z:density  w:���R�ΐ��̒� )

uniform		highp	vec4	uToonOutLineSize ;	// �g�D�[���̗֊s���̑傫��
uniform		lowp	vec4	uDifSrc_SpeSrc_MulSpeCol ;	// x:�f�B�t���[�Y�J���[( 0.0:�}�e���A��  1.0:���_ )  y:�X�y�L�����J���[(   0.0:�}�e���A��  1.0:���_ )  z:�X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )

uniform		highp	vec4	uSMLVPMat[ 12 /*  [ 3 ][ 4 ]  */ ] ;	// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������

uniform		mediump	vec4	uTexMat[ 6  /*  [ DX_VS_CONSTF_TEXTURE_MATRIX_NUM ][ 2 ]  */ ] ;	// �e�N�X�`�����W����p�s��
uniform		highp	vec4	uLWMat[ 162 /*  DX_VS_CONSTF_WORLD_MAT_NUM      * 3  */ ] ;	// ���[�J���@���@���[���h�s��





// main�֐�
void main( void )
{
	ivec4			lBoneIndex ;
	highp	vec4	lLWMat[ 3 ] ;
	highp	vec4	lLocalPos ;
	highp	vec4	lWorldPos ;
	highp	vec4	lViewPos ;
	mediump	vec3	lWorldNrm ;
	mediump	vec3	lWorldTan ;
	mediump	vec3	lWorldBin ;
	mediump	vec3	lViewNrm ;
	mediump	vec3	lViewTan ;
	mediump	vec3	lViewBin ;
	mediump	vec4	lTexUVTemp ;
#if SHADOWMAP != 0
	highp	vec4	lLViewPos ;
#endif


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	#ifdef SKINMESH

		// �X�L�����b�V��

		// �u�����h�s��̍쐬
		lBoneIndex = aBlendInd0 ;
		lLWMat[ 0 ]  = uLWMat[ lBoneIndex.x + 0 ] * aBlendWeight0.xxxx;
		lLWMat[ 1 ]  = uLWMat[ lBoneIndex.x + 1 ] * aBlendWeight0.xxxx;
		lLWMat[ 2 ]  = uLWMat[ lBoneIndex.x + 2 ] * aBlendWeight0.xxxx;

		lLWMat[ 0 ] += uLWMat[ lBoneIndex.y + 0 ] * aBlendWeight0.yyyy;
		lLWMat[ 1 ] += uLWMat[ lBoneIndex.y + 1 ] * aBlendWeight0.yyyy;
		lLWMat[ 2 ] += uLWMat[ lBoneIndex.y + 2 ] * aBlendWeight0.yyyy;

		lLWMat[ 0 ] += uLWMat[ lBoneIndex.z + 0 ] * aBlendWeight0.zzzz;
		lLWMat[ 1 ] += uLWMat[ lBoneIndex.z + 1 ] * aBlendWeight0.zzzz;
		lLWMat[ 2 ] += uLWMat[ lBoneIndex.z + 2 ] * aBlendWeight0.zzzz;

		lLWMat[ 0 ] += uLWMat[ lBoneIndex.w + 0 ] * aBlendWeight0.wwww;
		lLWMat[ 1 ] += uLWMat[ lBoneIndex.w + 1 ] * aBlendWeight0.wwww;
		lLWMat[ 2 ] += uLWMat[ lBoneIndex.w + 2 ] * aBlendWeight0.wwww;

		#ifdef BONE8

			lBoneIndex = aBlendInd1 ;
			lLWMat[ 0 ] += uLWMat[ lBoneIndex.x + 0 ] * aBlendWeight1.xxxx;
			lLWMat[ 1 ] += uLWMat[ lBoneIndex.x + 1 ] * aBlendWeight1.xxxx;
			lLWMat[ 2 ] += uLWMat[ lBoneIndex.x + 2 ] * aBlendWeight1.xxxx;

			lLWMat[ 0 ] += uLWMat[ lBoneIndex.y + 0 ] * aBlendWeight1.yyyy;
			lLWMat[ 1 ] += uLWMat[ lBoneIndex.y + 1 ] * aBlendWeight1.yyyy;
			lLWMat[ 2 ] += uLWMat[ lBoneIndex.y + 2 ] * aBlendWeight1.yyyy;

			lLWMat[ 0 ] += uLWMat[ lBoneIndex.z + 0 ] * aBlendWeight1.zzzz;
			lLWMat[ 1 ] += uLWMat[ lBoneIndex.z + 1 ] * aBlendWeight1.zzzz;
			lLWMat[ 2 ] += uLWMat[ lBoneIndex.z + 2 ] * aBlendWeight1.zzzz;

			lLWMat[ 0 ] += uLWMat[ lBoneIndex.w + 0 ] * aBlendWeight1.wwww;
			lLWMat[ 1 ] += uLWMat[ lBoneIndex.w + 1 ] * aBlendWeight1.wwww;
			lLWMat[ 2 ] += uLWMat[ lBoneIndex.w + 2 ] * aBlendWeight1.wwww;

		#endif // BONE8

	#endif	// SKINMESH

	// ���[�J�����W�̃Z�b�g
	lLocalPos.xyz = aPos ;
	lLocalPos.w = 1.0 ;

	// ���W�v�Z( ���[�J�����r���[���v���W�F�N�V���� )
	#ifdef SKINMESH
		lWorldPos.x = dot( lLocalPos, lLWMat[ 0 ] ) ;
		lWorldPos.y = dot( lLocalPos, lLWMat[ 1 ] ) ;
		lWorldPos.z = dot( lLocalPos, lLWMat[ 2 ] ) ;
	#else
		lWorldPos.x = dot( lLocalPos, uLWMat[ 0 ] ) ;
		lWorldPos.y = dot( lLocalPos, uLWMat[ 1 ] ) ;
		lWorldPos.z = dot( lLocalPos, uLWMat[ 2 ] ) ;
	#endif
	lWorldPos.w = 1.0 ;

	lViewPos.x = dot( lWorldPos, uViewMat[ 0 ] ) ;
	lViewPos.y = dot( lWorldPos, uViewMat[ 1 ] ) ;
	lViewPos.z = dot( lWorldPos, uViewMat[ 2 ] ) ;
	lViewPos.w = 1.0 ;

	gl_Position.x = dot( lViewPos, uProjMat[ 0 ] ) ;
	gl_Position.y = dot( lViewPos, uProjMat[ 1 ] ) ;
	gl_Position.z = dot( lViewPos, uProjMat[ 2 ] ) ;
	gl_Position.w = dot( lViewPos, uProjMat[ 3 ] ) ;
	
	// ���W( �r���[��� )��ۑ�
	vVPos = lViewPos.xyz;
	
	// �@�����v�Z
	#ifdef SKINMESH
		lWorldNrm.x = dot( aNrm, lLWMat[ 0 ].xyz ) ;
		lWorldNrm.y = dot( aNrm, lLWMat[ 1 ].xyz ) ;
		lWorldNrm.z = dot( aNrm, lLWMat[ 2 ].xyz ) ;
	#else
		lWorldNrm.x = dot( aNrm, uLWMat[ 0 ].xyz ) ;
		lWorldNrm.y = dot( aNrm, uLWMat[ 1 ].xyz ) ;
		lWorldNrm.z = dot( aNrm, uLWMat[ 2 ].xyz ) ;
	#endif

	lViewNrm.x = dot( lWorldNrm, uViewMat[ 0 ].xyz ) ;
	lViewNrm.y = dot( lWorldNrm, uViewMat[ 1 ].xyz ) ;
	lViewNrm.z = dot( lWorldNrm, uViewMat[ 2 ].xyz ) ;

	// �@��( �r���[��� )��ۑ�
	vVNrm = lViewNrm;

	#ifdef BUMPMAP

		// �]�@���A�ڐ����r���[��Ԃɓ��e����
		#ifdef SKINMESH
			lWorldTan.x = dot( aTan, lLWMat[ 0 ].xyz ) ;
			lWorldTan.y = dot( aTan, lLWMat[ 1 ].xyz ) ;
			lWorldTan.z = dot( aTan, lLWMat[ 2 ].xyz ) ;

			lWorldBin.x = dot( aBin, lLWMat[ 0 ].xyz ) ;
			lWorldBin.y = dot( aBin, lLWMat[ 1 ].xyz ) ;
			lWorldBin.z = dot( aBin, lLWMat[ 2 ].xyz ) ;
		#else
			lWorldTan.x = dot( aTan, uLWMat[ 0 ].xyz ) ;
			lWorldTan.y = dot( aTan, uLWMat[ 1 ].xyz ) ;
			lWorldTan.z = dot( aTan, uLWMat[ 2 ].xyz ) ;

			lWorldBin.x = dot( aBin, uLWMat[ 0 ].xyz ) ;
			lWorldBin.y = dot( aBin, uLWMat[ 1 ].xyz ) ;
			lWorldBin.z = dot( aBin, uLWMat[ 2 ].xyz ) ;
		#endif

		lViewTan.x = dot( lWorldTan, uViewMat[ 0 ].xyz ) ;
		lViewTan.y = dot( lWorldTan, uViewMat[ 1 ].xyz ) ;
		lViewTan.z = dot( lWorldTan, uViewMat[ 2 ].xyz ) ;

		lViewBin.x = dot( lWorldBin, uViewMat[ 0 ].xyz ) ;
		lViewBin.y = dot( lWorldBin, uViewMat[ 1 ].xyz ) ;
		lViewBin.z = dot( lWorldBin, uViewMat[ 2 ].xyz ) ;
		
		// �]�@���A�ڐ�( �r���[��� )��ۑ�
		vVTan = lViewTan;
		vVBin = lViewBin;

	#endif	// BUMPMAP

	// �f�B�t���[�Y�J���[���Z�b�g
	vDif  = uDifSrc_SpeSrc_MulSpeCol.x  > 0.5 ? aDif  : uMatDif ;
	
	// �X�y�L�����J���[���Z�b�g
	vSpc = ( uDifSrc_SpeSrc_MulSpeCol.y > 0.5 ? aSpc : uMatSpc ) * uDifSrc_SpeSrc_MulSpeCol.z ;

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )





	// �t�H�O�v�Z =============================================( �J�n )

	#if FOG_LINEAR != 0 || FOG_EXP != 0 || FOG_EXP2 != 0

		#ifdef FOG_LINEAR

			// ���`�t�H�O�v�Z
			vFog_SM2PosZ.x = lViewPos.z * uFog.y + uFog.x ;

		#endif

		#ifdef FOG_EXP

			// �w���t�H�O�v�Z 1.0 / pow( e, ���� * density )
			vFog_SM2PosZ.x = 1.0 / pow( abs( uFog.w ), lViewPos.z * uFog.z ) ;

		#endif

		#ifdef FOG_EXP2

			// �w���t�H�O�Q�v�Z 1.0 / pow( e, ( ���� * density ) * ( ���� * density ) )
			vFog_SM2PosZ.x = 1.0 / pow( abs( uFog.w ), ( lViewPos.z * uFog.z ) * ( lViewPos.z * uFog.z ) ) ;

		#endif

	#else // FOG_LINEAR || FOG_EXP || FOG_EXP2
	
		vFog_SM2PosZ.x = 1.0;

	#endif // FOG_LINEAR || FOG_EXP || FOG_EXP2

	// �t�H�O�v�Z =============================================( �I�� )

#if SHADOWMAP != 0
	// �[�x�e�p�̃��C�g���猩���ˉe���W���Z�o =================( �J�n )

	// ���[���h���W���V���h�E�}�b�v�O�̃��C�g�ݒ�̎ˉe���W�ɕϊ�
	vSM0Pos_SM2PosX.x = dot( lWorldPos, uSMLVPMat[  0 ] ) ;
	vSM0Pos_SM2PosX.y = dot( lWorldPos, uSMLVPMat[  1 ] ) ;
	vSM0Pos_SM2PosX.z = dot( lWorldPos, uSMLVPMat[  2 ] ) ;

	// ���[���h���W���V���h�E�}�b�v�P�̃��C�g�ݒ�̎ˉe���W�ɕϊ�
	vSM1Pos_SM2PosY.x = dot( lWorldPos, uSMLVPMat[  4 ] ) ;
	vSM1Pos_SM2PosY.y = dot( lWorldPos, uSMLVPMat[  5 ] ) ;
	vSM1Pos_SM2PosY.z = dot( lWorldPos, uSMLVPMat[  6 ] ) ;

	// ���[���h���W���V���h�E�}�b�v�Q�̃��C�g�ݒ�̎ˉe���W�ɕϊ�
	vSM0Pos_SM2PosX.w = dot( lWorldPos, uSMLVPMat[  8 ] ) ;
	vSM1Pos_SM2PosY.w = dot( lWorldPos, uSMLVPMat[  9 ] ) ;
	vFog_SM2PosZ.y    = dot( lWorldPos, uSMLVPMat[ 10 ] ) ;

	// �[�x�e�p�̃��C�g���猩���ˉe���W���Z�o =================( �I�� )
#endif

	// �e�N�X�`�����W�̃Z�b�g
	lTexUVTemp.z = 1.0 ;
	lTexUVTemp.w = 1.0 ;

	lTexUVTemp.xy = aTexUV0 ;
	vTexUV0_1.x = dot( lTexUVTemp, uTexMat[ 0 ] ) ;
	vTexUV0_1.y = dot( lTexUVTemp, uTexMat[ 1 ] ) ;

	lTexUVTemp.xy = aTexUV1 ;
	vTexUV0_1.z = dot( lTexUVTemp, uTexMat[ 2 ] ) ;
	vTexUV0_1.w = dot( lTexUVTemp, uTexMat[ 3 ] ) ;
}

