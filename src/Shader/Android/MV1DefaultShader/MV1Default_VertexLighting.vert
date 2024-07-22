// ���_�V�F�[�_�[�̓���
attribute	highp	vec3	aPos ;			// ���W( ���[�J����� )
attribute	mediump	vec3	aNrm ;			// �@��
attribute	mediump	vec4	aDif ;			// �f�B�t���[�Y�J���[
attribute	mediump	vec4	aSpc ;			// �X�y�L�����J���[
attribute	mediump	vec4	aTexUV0F4 ;		// �e�N�X�`�����W�O
attribute	mediump	vec4	aTexUV1F4 ;		// �e�N�X�`�����W�P

#if BUMPMAP != 0 || BUMPMAP_VERTEXDATAONLY != 0
// �o���v�}�b�v
attribute	mediump	vec3	aTan ;			// �ڐ�( ���[�J����� )
attribute	mediump	vec3	aBin ;			// �]�@��( ���[�J����� )
#endif // BUMPMAP

#ifdef SKINMESH
	// �X�L�j���O���b�V��
	attribute	mediump	vec4	aBlendInd0 ;		// �{�[�������p Float�^�萔�z��C���f�b�N�X�O
	attribute	lowp	vec4	aBlendWeight0 ;		// �{�[�������p�E�G�C�g�l�O

	#ifdef BONE8

		attribute	mediump	vec4	aBlendInd1 ;		// �{�[�������p Float�^�萔�z��C���f�b�N�X�P
		attribute	lowp	vec4	aBlendWeight1 ;		// �{�[�������p�E�G�C�g�l�P

	#endif // BONE8

#endif // SKINMESH

// ���_�V�F�[�_�[�̏o��
varying		mediump	vec4	vDif ;				// �f�B�t���[�Y�J���[
varying		mediump	vec4	vSpc ;				// �X�y�L�����J���[
varying		mediump	vec4	vTexUV0_1 ;			// xy:�e�N�X�`�����W zw:�T�u�e�N�X�`�����W

varying		highp	vec4	vVtoEyeSM2PosZ ;	// ���_���W���王���ւ̃x�N�g��( �r���[��� )�ƃV���h�E�}�b�v�Q�̃��C�gZ���W( w )
varying		highp	vec4	vNrmFog ;			// x.y.z:�@��( �r���[��� )  w:�t�H�O�p�����[�^

#if LG0_USE != 0
varying		highp	vec4	vLight0DirGen ;		// xyz:���C�g�O�̋t�x�N�g��( �r���[��� ) w:���C�g�O�������
#endif
#if LG1_USE != 0
varying		highp	vec4	vLight1DirGen ;		// xyz:���C�g�P�̋t�x�N�g��( �r���[��� ) w:���C�g�P�������
#endif
#if LG2_USE != 0
varying		highp	vec4	vLight2DirGen ;		// xyz:���C�g�Q�̋t�x�N�g��( �r���[��� ) w:���C�g�Q�������
#endif

#if SHADOWMAP != 0 || SHADOWMAP_DRAW != 0
varying		highp	vec4	vSM0Pos_SM2PosX ;	// �V���h�E�}�b�v�O�̃��C�g���W( x, y, z )�ƃV���h�E�}�b�v�Q�̃��C�gX���W( w )
#endif
#if SHADOWMAP != 0
varying		highp	vec4	vSM1Pos_SM2PosY ;	// �V���h�E�}�b�v�P�̃��C�g���W( x, y, z )�ƃV���h�E�}�b�v�Q�̃��C�gY���W( w )
#endif



uniform		mediump	vec4	uAmb_Emi ;			// �G�~�b�V�u�J���[�{�A���r�G���g�J���[( �G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[ )

uniform		mediump	vec4	uMatDif ;			// �f�B�t���[�Y�J���[
uniform		mediump	vec4	uMatSpc ;			// �X�y�L�����J���[
uniform		mediump	float	uMatPow ;			// �X�y�L�����̋���

uniform		highp	vec3	uLightPos[ 3 ] ;					// ���W( �r���[��� )
uniform		mediump	vec3	uLightDir[ 3 ] ;					// ����( �r���[��� )
uniform		mediump	vec4	uLightDif[ 3 ] ;					// �f�B�t���[�Y�J���[
uniform		mediump	vec4	uLightSpc[ 3 ] ;					// �X�y�L�����J���[
uniform		mediump	vec4	uLightAmb[ 3 ] ;					// �A���r�G���g�J���[
uniform		highp	vec4	uLightRange_FallOff_AT0_AT1[ 3 ] ;	// x:�L������  y:�X�|�b�g���C�g�pFllOff  z:�����ɂ�錸�������p�p�����[�^�O  w:�����ɂ�錸�������p�p�����[�^�P
uniform		highp	vec4	uLightAT2_SpotP0_SpotP1[ 3 ] ;		// x:�����ɂ�錸�������p�p�����[�^�Q  y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0 ) )  z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0 / ( cos( Theta / 2.0 ) - cos( Phi / 2.0 ) ) )

uniform		highp	vec4	uProjMat[ 4 ] ;		// �r���[�@���@�v���W�F�N�V�����s��
uniform		highp	vec4	uViewMat[ 3 ] ;		// ���[���h�@���@�r���[�s��
uniform		highp	vec4	uFog ;				// �t�H�O�p�p�����[�^( x:end/(end - start)  y:-1/(end - start)  z:density  w:���R�ΐ��̒� )

uniform		highp	vec4	uToonOutLineSize ;	// �g�D�[���̗֊s���̑傫��
uniform		lowp	vec4	uDifSrc_SpeSrc_MulSpeCol ;	// x:�f�B�t���[�Y�J���[( 0.0:�}�e���A��  1.0:���_ )  y:�X�y�L�����J���[(   0.0:�}�e���A��  1.0:���_ )  z:�X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )

uniform		highp	vec4	uSMLVPMat[ 12 /* [ 3 ][ 4 ] */ ] ;	// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������

uniform		mediump	vec4	uTexMat[ 6 /* [ DX_VS_CONSTF_TEXTURE_MATRIX_NUM ][ 2 ] */ ] ;	// �e�N�X�`�����W����p�s��
uniform		highp	vec4	uLWMat[ 162 /* DX_VS_CONSTF_WORLD_MAT_NUM * 3 */ ] ;		// ���[�J���@���@���[���h�s��


// main�֐�
void main( void )
{
			ivec4	lBoneIndex ;
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
	highp	vec3	lBumpTemp ;
	mediump	vec4	lTotalDif ;
	mediump	vec4	lTotalSpc ;
	mediump	vec3	lLightDir ;
	mediump	float	lTotalGen ;
	highp	vec3	lLightTemp ;
	highp	float	lLightDistPow2 ;
	mediump	float	lLightGen ;
	highp	float	lLightDirCosA ;
	highp	vec3	lLightHalfVec ;
	highp	vec4	lLightLitDest ;
	mediump	vec4	lDifColor;
#if USE_SPE != 0
	mediump	vec4	lSpeColor;
#endif
#if SHADOWMAP != 0
	highp	vec4	lLViewPos ;
#endif

	lDifColor = uDifSrc_SpeSrc_MulSpeCol.x  > 0.5 ? aDif  : uMatDif ;
	
#if USE_SPE != 0
	lSpeColor = ( uDifSrc_SpeSrc_MulSpeCol.y > 0.5 ? aSpc : uMatSpc ) * uDifSrc_SpeSrc_MulSpeCol.z ;
#endif

	vVtoEyeSM2PosZ.xyz  = vec3( 0.0, 0.0, 0.0 ) ;
	vSpc				= vec4( 0.0, 0.0, 0.0, 0.0 ) ;
	vNrmFog				= vec4( 0.0, 0.0, 0.0, 1.0 ) ;

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	#ifdef SKINMESH

		// �X�L�����b�V��

		// �u�����h�s��̍쐬
		lBoneIndex.x = int( aBlendInd0.x ) ;
		lBoneIndex.y = int( aBlendInd0.y ) ;
		lBoneIndex.z = int( aBlendInd0.z ) ;
		lBoneIndex.w = int( aBlendInd0.w ) ;
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

			lBoneIndex.x = int( aBlendInd1.x ) ;
			lBoneIndex.y = int( aBlendInd1.y ) ;
			lBoneIndex.z = int( aBlendInd1.z ) ;
			lBoneIndex.w = int( aBlendInd1.w ) ;
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

	#ifdef TOONOUTLINE

		// ���W�v�Z( ���[�J�������[���h )
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

		#ifdef SKINMESH
			lWorldNrm.x = dot( aNrm, lLWMat[ 0 ].xyz ) ;
			lWorldNrm.y = dot( aNrm, lLWMat[ 1 ].xyz ) ;
			lWorldNrm.z = dot( aNrm, lLWMat[ 2 ].xyz ) ;
		#else
			lWorldNrm.x = dot( aNrm, uLWMat[ 0 ].xyz ) ;
			lWorldNrm.y = dot( aNrm, uLWMat[ 1 ].xyz ) ;
			lWorldNrm.z = dot( aNrm, uLWMat[ 2 ].xyz ) ;
		#endif

		// �֊s���̑������@�������Ɉړ�����
		lWorldPos.xyz += lWorldNrm * uToonOutLineSize.x ;

		// ���[���h���r���[
		lViewPos.x = dot( lWorldPos, uViewMat[ 0 ] ) ;
		lViewPos.y = dot( lWorldPos, uViewMat[ 1 ] ) ;
		lViewPos.z = dot( lWorldPos, uViewMat[ 2 ] ) ;
		lViewPos.w = 1.0 ;

		// �r���[���v���W�F�N�V����
		gl_Position.x = dot( lViewPos, uProjMat[ 0 ] ) ;
		gl_Position.y = dot( lViewPos, uProjMat[ 1 ] ) ;
		gl_Position.z = dot( lViewPos, uProjMat[ 2 ] ) ;
		gl_Position.w = dot( lViewPos, uProjMat[ 3 ] ) ;

	#else  // TOONOUTLINE

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

	#endif // TOONOUTLINE

	#ifdef BUMPMAP

		// �]�@���A�ڐ��A�@�����r���[��Ԃɓ��e����
		#ifdef SKINMESH
			lWorldTan.x = dot( aTan, lLWMat[ 0 ].xyz ) ;
			lWorldTan.y = dot( aTan, lLWMat[ 1 ].xyz ) ;
			lWorldTan.z = dot( aTan, lLWMat[ 2 ].xyz ) ;

			lWorldBin.x = dot( aBin, lLWMat[ 0 ].xyz ) ;
			lWorldBin.y = dot( aBin, lLWMat[ 1 ].xyz ) ;
			lWorldBin.z = dot( aBin, lLWMat[ 2 ].xyz ) ;

			lWorldNrm.x = dot( aNrm, lLWMat[ 0 ].xyz ) ;
			lWorldNrm.y = dot( aNrm, lLWMat[ 1 ].xyz ) ;
			lWorldNrm.z = dot( aNrm, lLWMat[ 2 ].xyz ) ;
		#else
			lWorldTan.x = dot( aTan, uLWMat[ 0 ].xyz ) ;
			lWorldTan.y = dot( aTan, uLWMat[ 1 ].xyz ) ;
			lWorldTan.z = dot( aTan, uLWMat[ 2 ].xyz ) ;

			lWorldBin.x = dot( aBin, uLWMat[ 0 ].xyz ) ;
			lWorldBin.y = dot( aBin, uLWMat[ 1 ].xyz ) ;
			lWorldBin.z = dot( aBin, uLWMat[ 2 ].xyz ) ;

			lWorldNrm.x = dot( aNrm, uLWMat[ 0 ].xyz ) ;
			lWorldNrm.y = dot( aNrm, uLWMat[ 1 ].xyz ) ;
			lWorldNrm.z = dot( aNrm, uLWMat[ 2 ].xyz ) ;
		#endif

		lViewTan.x = dot( lWorldTan, uViewMat[ 0 ].xyz ) ;
		lViewTan.y = dot( lWorldTan, uViewMat[ 1 ].xyz ) ;
		lViewTan.z = dot( lWorldTan, uViewMat[ 2 ].xyz ) ;

		lViewBin.x = dot( lWorldBin, uViewMat[ 0 ].xyz ) ;
		lViewBin.y = dot( lWorldBin, uViewMat[ 1 ].xyz ) ;
		lViewBin.z = dot( lWorldBin, uViewMat[ 2 ].xyz ) ;

		lViewNrm.x = dot( lWorldNrm, uViewMat[ 0 ].xyz ) ;
		lViewNrm.y = dot( lWorldNrm, uViewMat[ 1 ].xyz ) ;
		lViewNrm.z = dot( lWorldNrm, uViewMat[ 2 ].xyz ) ;

	#endif	// BUMPMAP


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )

	#if LG_USE == 0 || BUMPMAP == 1 || PHONG == 1

		// ���C�g���g�p���Ȃ����A�o���v�}�b�v���̓t�H���V�F�[�f�B���O�̏ꍇ�̓}�e���A��( or ���_ )�J���[�����̂܂܏o��
		vDif  = lDifColor ;

		#if USE_SPE != 0
			vSpc = lSpeColor ;
		#endif
		
		#if BUMPMAP == 0 && PHONG != 0
		
			// �@�����r���[��Ԃ̊p�x�ɕϊ�
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

			// �@����ۑ�
			vNrmFog.xyz = lViewNrm ;

		#endif // PHONG

	#endif // LG_USE == 0 || BUMPMAP == 1 || PHONG == 1





	// ���C�g�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )
	#if LG_USE != 0

		#ifdef BUMPMAP

			#if USE_SPE != 0
				// ���_���W���王�_�ւ̃x�N�g����ڒ��Ԃɓ��e�����㐳�K�����ĕۑ�
				lBumpTemp.x = dot( lViewTan, -lViewPos.xyz ) ;
				lBumpTemp.y = dot( lViewBin, -lViewPos.xyz ) ;
				lBumpTemp.z = dot( lViewNrm, -lViewPos.xyz ) ;
				vVtoEyeSM2PosZ.xyz = normalize( lBumpTemp ) ;
			#endif

		#else // BUMPMAP 

			// �@�����r���[��Ԃ̊p�x�ɕϊ�
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

			// �f�B�t���[�Y�J���[�ƃX�y�L�����J���[�̒~�ϒl�̏�����
			lTotalDif = vec4( 0, 0, 0, 0 ) ;
			lTotalSpc = vec4( 0, 0, 0, 0 ) ;

			#ifdef PHONG

				#if USE_SPE != 0
					// ���_���W���王�_�ւ̃x�N�g���𐳋K�����ĕۑ�
					vVtoEyeSM2PosZ.xyz = normalize( -lViewPos.xyz ) ;
				#endif

				// �@����ۑ�
				vNrmFog.xyz = lViewNrm ;

			#endif // PHONG

		#endif // BUMPMAP







		// ���C�g0�̏��� ***********************************************************************************************************************************( �J�n )
#if LG0_USE != 0

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �J�n )

	#if LG0_DIR != 0

		// ���C�g�̕����v�Z
		lLightDir = uLightDir[ 0 ] ;

	#else  // LG0_DIR

		// ���C�g�����x�N�g���̌v�Z
		lLightDir = normalize( lViewPos.xyz - uLightPos[ 0 ] ) ;

	#endif  // LG0_DIR

	// ���C�g�̏���������
	vLight0DirGen = vec4( 0.0, 0.0, 0.0, 0.0 ) ;

	// ���C�g�̌����̋t�x�N�g����ڒn��Ԃɕϊ�
	#ifdef BUMPMAP

		lLightTemp.x = dot( lViewTan, -lLightDir ) ;
		lLightTemp.y = dot( lViewBin, -lLightDir ) ;
		lLightTemp.z = dot( lViewNrm, -lLightDir ) ;
		vLight0DirGen.xyz = normalize( lLightTemp.xyz ) ;

	#else // BUMPMAP
		#if PHONG != 0

			// ���C�g�̌����̋t�x�N�g����ۑ�
			vLight0DirGen.xyz = -lLightDir ;

		#endif // PHONG
	#endif // BUMPMAP

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �I�� )


	// �����E�X�|�b�g���C�g�����l�v�Z ==========================( �J�n )
	#if LG0_SPOT != 0 || LG0_POINT != 0

		// ���������v�Z ------------------

		// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂� lLightTemp.x = ( POS - L0_POS ) * ( POS - L0_POS )
		lLightTemp = lViewPos.xyz - uLightPos[ 0 ] ;
		lLightDistPow2 = dot( lLightTemp, lLightTemp ) ;

		// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
		lLightGen = 1.0 / ( uLightRange_FallOff_AT0_AT1[ 0 ].z + uLightRange_FallOff_AT0_AT1[ 0 ].w * sqrt( lLightDistPow2 ) + uLightAT2_SpotP0_SpotP1[ 0 ].x * lLightDistPow2 ) ;

		// �X�|�b�g���C�g�����v�Z --------

		#if LG0_SPOT != 0

			// ���C�g�����x�N�g���ƃ��C�g�ʒu���璸�_�ʒu�ւ̃x�N�g���̓���( ���� Cos a )���v�Z 
			lLightDirCosA = dot( lLightDir, uLightDir[ 0 ].xyz ) ;

			// �X�|�b�g���C�g�����v�Z  pow( falloff, ( ( Cos a - Cos f ) / ( Cos q - Cos f ) ) )
			lLightGen *= clamp( pow( abs( max( lLightDirCosA - uLightAT2_SpotP0_SpotP1[ 0 ].y, 0.0 ) * uLightAT2_SpotP0_SpotP1[ 0 ].z ), uLightRange_FallOff_AT0_AT1[ 0 ].y ), 0.0, 1.0 ) ;

		#endif // LG0_SPOT

		// �L�������O�������猸�������ő�ɂ��鏈��
		lLightGen *= step( lLightDistPow2, uLightRange_FallOff_AT0_AT1[ 0 ].x ) ;

		// �o���v�}�b�v or �t�H���V�F�[�f�B���O�p�Ɍ�������ۑ�����
		#if PHONG != 0 || BUMPMAP != 0
			vLight0DirGen.w = lLightGen ;
		#endif // PHONG || BUMPMAP

	#endif // LG0_SPOT || LG0_POINT
	// �����E�X�|�b�g���C�g�����l�v�Z =========================( �I�� )




	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �J�n )
	#if BUMPMAP == 0 && PHONG == 0

		lLightLitDest.y = clamp( dot( lViewNrm, -lLightDir ), 0.0, 1.0 ) ;

		#ifdef USE_SPE

			// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
			lLightHalfVec = normalize( normalize( -lViewPos.xyz ) - lLightDir ) ;

			// lLightLitDest.z = pow( max( 0.0, N * H ), uMatPow )
			lLightLitDest.z = pow( max( 0.0, dot( lViewNrm, lLightHalfVec ) ), uMatPow ) ;

		#endif // USE_SPE

	#endif // BUMPMAP == 0 && PHONG == 0
	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �I�� )





	// �f�B�t���[�Y�J���[�v�Z =======================================( �J�n )

	#if BUMPMAP == 0 && PHONG == 0

		#if LG0_SPOT != 0 || LG0_POINT != 0

			// �f�B�t���[�Y���C�g�~�ϒl += �����E�X�|�b�g���C�g�p�x�����l * ( �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� )
			lTotalDif.xyz += lLightGen * ( lLightLitDest.y * uLightDif[ 0 ] * lDifColor.xyz + uLightAmb[ 0 ].xyz ) ;

		#else  // LG0_SPOT || LG0_POINT

			// �f�B�t���[�Y���C�g�~�ϒl += �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
			lTotalDif.xyz += lLightLitDest.y * uLightDif[ 0 ] * lDifColor.xyz + uLightAmb[ 0 ].xyz ;

		#endif // LG0_SPOT || LG0_POINT

	#endif // BUMPMAP == 0 && PHONG == 0

	// �f�B�t���[�Y�J���[�v�Z =======================================( �I�� )





	// �X�y�L�����J���[�v�Z =======================================( �J�n )

	#ifdef USE_SPE

		#if BUMPMAP == 0 && PHONG == 0

			#if LG0_SPOT != 0 || LG0_POINT != 0

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * �����E�X�|�b�g���C�g���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightGen * lLightLitDest.z * uLightSpc[ 0 ] ;

			#else	// LG0_SPOT || LG0_POINT

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightLitDest.z * uLightSpc[ 0 ] ;

			#endif	// LG0_SPOT || LG0_POINT

		#endif // BUMPMAP == 0 && PHONG == 0

	#endif // USE_SPE

	// �X�y�L�����J���[�v�Z =======================================( �I�� )




#endif  // LG0_USE
// ���C�g0�̏��� ***********************************************************************************************************************************( �I�� )








		// ���C�g1�̏��� ***********************************************************************************************************************************( �J�n )
#if LG1_USE != 0

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �J�n )

	#if LG1_DIR != 0

		// ���C�g�̕����v�Z
		lLightDir = uLightDir[ 1 ] ;

	#else  // LG1_DIR

		// ���C�g�����x�N�g���̌v�Z
		lLightDir = normalize( lViewPos.xyz - uLightPos[ 1 ] ) ;

	#endif  // LG1_DIR

	// ���C�g�̏���������
	vLight1DirGen = vec4( 0.0, 0.0, 0.0, 0.0 ) ;

	// ���C�g�̌����̋t�x�N�g����ڒn��Ԃɕϊ�
	#ifdef BUMPMAP

		lLightTemp.x = dot( lViewTan, -lLightDir ) ;
		lLightTemp.y = dot( lViewBin, -lLightDir ) ;
		lLightTemp.z = dot( lViewNrm, -lLightDir ) ;
		vLight1DirGen.xyz = normalize( lLightTemp.xyz ) ;

	#else // BUMPMAP
		#if PHONG != 0

			// ���C�g�̌����̋t�x�N�g����ۑ�
			vLight1DirGen.xyz = -lLightDir ;

		#endif // PHONG
	#endif // BUMPMAP

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �I�� )


	// �����E�X�|�b�g���C�g�����l�v�Z ==========================( �J�n )
	#if LG1_SPOT != 0 || LG1_POINT != 0

		// ���������v�Z ------------------

		// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂� lLightTemp.x = ( POS - L1_POS ) * ( POS - L1_POS )
		lLightTemp = lViewPos.xyz - uLightPos[ 1 ] ;
		lLightDistPow2 = dot( lLightTemp, lLightTemp ) ;

		// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
		lLightGen = 1.0 / ( uLightRange_FallOff_AT0_AT1[ 1 ].z + uLightRange_FallOff_AT0_AT1[ 1 ].w * sqrt( lLightDistPow2 ) + uLightAT2_SpotP0_SpotP1[ 1 ].x * lLightDistPow2 ) ;

		// �X�|�b�g���C�g�����v�Z --------

		#if LG1_SPOT != 0

			// ���C�g�����x�N�g���ƃ��C�g�ʒu���璸�_�ʒu�ւ̃x�N�g���̓���( ���� Cos a )���v�Z 
			lLightDirCosA = dot( lLightDir, uLightDir[ 1 ].xyz ) ;

			// �X�|�b�g���C�g�����v�Z  pow( falloff, ( ( Cos a - Cos f ) / ( Cos q - Cos f ) ) )
			lLightGen *= clamp( pow( abs( max( lLightDirCosA - uLightAT2_SpotP0_SpotP1[ 1 ].y, 0.0 ) * uLightAT2_SpotP0_SpotP1[ 1 ].z ), uLightRange_FallOff_AT0_AT1[ 1 ].y ), 0.0, 1.0 ) ;

		#endif // LG1_SPOT

		// �L�������O�������猸�������ő�ɂ��鏈��
		lLightGen *= step( lLightDistPow2, uLightRange_FallOff_AT0_AT1[ 1 ].x ) ;

		// �o���v�}�b�v or �t�H���V�F�[�f�B���O�p�Ɍ�������ۑ�����
		#if PHONG != 0 || BUMPMAP != 0
			vLight1DirGen.w = lLightGen ;
		#endif // PHONG || BUMPMAP

	#endif // LG1_SPOT || LG1_POINT
	// �����E�X�|�b�g���C�g�����l�v�Z =========================( �I�� )




	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �J�n )
	#if BUMPMAP == 0 && PHONG == 0

		lLightLitDest.y = clamp( dot( lViewNrm, -lLightDir ), 0.0, 1.0 ) ;

		#ifdef USE_SPE

			// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
			lLightHalfVec = normalize( normalize( -lViewPos.xyz ) - lLightDir ) ;

			// lLightLitDest.z = pow( max( 0.0, N * H ), uMatPow )
			lLightLitDest.z = pow( max( 0.0, dot( lViewNrm, lLightHalfVec ) ), uMatPow ) ;

		#endif // USE_SPE

	#endif // BUMPMAP == 0 && PHONG == 0
	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �I�� )





	// �f�B�t���[�Y�J���[�v�Z =======================================( �J�n )

	#if BUMPMAP == 0 && PHONG == 0

		#if LG1_SPOT != 0 || LG1_POINT != 0

			// �f�B�t���[�Y���C�g�~�ϒl += �����E�X�|�b�g���C�g�p�x�����l * ( �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� )
			lTotalDif.xyz += lLightGen * ( lLightLitDest.y * uLightDif[ 1 ] * lDifColor.xyz + uLightAmb[ 1 ].xyz ) ;

		#else  // LG1_SPOT || LG1_POINT

			// �f�B�t���[�Y���C�g�~�ϒl += �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
			lTotalDif.xyz += lLightLitDest.y * uLightDif[ 1 ] * lDifColor.xyz + uLightAmb[ 1 ].xyz ;

		#endif // LG1_SPOT || LG1_POINT

	#endif // BUMPMAP == 0 && PHONG == 0

	// �f�B�t���[�Y�J���[�v�Z =======================================( �I�� )





	// �X�y�L�����J���[�v�Z =======================================( �J�n )

	#ifdef USE_SPE

		#if BUMPMAP == 0 && PHONG == 0

			#if LG1_SPOT != 0 || LG1_POINT != 0

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * �����E�X�|�b�g���C�g���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightGen * lLightLitDest.z * uLightSpc[ 1 ] ;

			#else	// LG1_SPOT || LG1_POINT

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightLitDest.z * uLightSpc[ 1 ] ;

			#endif	// LG1_SPOT || LG1_POINT

		#endif // BUMPMAP == 0 && PHONG == 0

	#endif // USE_SPE

	// �X�y�L�����J���[�v�Z =======================================( �I�� )




#endif  // LG1_USE
// ���C�g1�̏��� ***********************************************************************************************************************************( �I�� )








		// ���C�g2�̏��� ***********************************************************************************************************************************( �J�n )
#if LG2_USE != 0

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �J�n )

	#if LG2_DIR != 0

		// ���C�g�̕����v�Z
		lLightDir = uLightDir[ 2 ] ;

	#else  // LG2_DIR

		// ���C�g�����x�N�g���̌v�Z
		lLightDir = normalize( lViewPos.xyz - uLightPos[ 2 ] ) ;

	#endif  // LG2_DIR

	// ���C�g�̏���������
	vLight2DirGen = vec4( 0.0, 0.0, 0.0, 0.0 ) ;

	// ���C�g�̌����̋t�x�N�g����ڒn��Ԃɕϊ�
	#ifdef BUMPMAP

		lLightTemp.x = dot( lViewTan, -lLightDir ) ;
		lLightTemp.y = dot( lViewBin, -lLightDir ) ;
		lLightTemp.z = dot( lViewNrm, -lLightDir ) ;
		vLight2DirGen.xyz = normalize( lLightTemp.xyz ) ;

	#else // BUMPMAP
		#if PHONG != 0

			// ���C�g�̌����̋t�x�N�g����ۑ�
			vLight2DirGen.xyz = -lLightDir ;

		#endif // PHONG
	#endif // BUMPMAP

	// �f�B�t���[�Y�J���[�p�x�����v�Z�p�̃��C�g�̕��������O�v�Z ======( �I�� )


	// �����E�X�|�b�g���C�g�����l�v�Z ==========================( �J�n )
	#if LG2_SPOT != 0 || LG2_POINT != 0

		// ���������v�Z ------------------

		// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂� lLightTemp.x = ( POS - L2_POS ) * ( POS - L2_POS )
		lLightTemp = lViewPos.xyz - uLightPos[ 2 ] ;
		lLightDistPow2 = dot( lLightTemp, lLightTemp ) ;

		// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
		lLightGen = 1.0 / ( uLightRange_FallOff_AT0_AT1[ 2 ].z + uLightRange_FallOff_AT0_AT1[ 2 ].w * sqrt( lLightDistPow2 ) + uLightAT2_SpotP0_SpotP1[ 2 ].x * lLightDistPow2 ) ;

		// �X�|�b�g���C�g�����v�Z --------

		#if LG2_SPOT != 0

			// ���C�g�����x�N�g���ƃ��C�g�ʒu���璸�_�ʒu�ւ̃x�N�g���̓���( ���� Cos a )���v�Z 
			lLightDirCosA = dot( lLightDir, uLightDir[ 2 ].xyz ) ;

			// �X�|�b�g���C�g�����v�Z  pow( falloff, ( ( Cos a - Cos f ) / ( Cos q - Cos f ) ) )
			lLightGen *= clamp( pow( abs( max( lLightDirCosA - uLightAT2_SpotP0_SpotP1[ 2 ].y, 0.0 ) * uLightAT2_SpotP0_SpotP1[ 2 ].z ), uLightRange_FallOff_AT0_AT1[ 2 ].y ), 0.0, 1.0 ) ;

		#endif // LG2_SPOT

		// �L�������O�������猸�������ő�ɂ��鏈��
		lLightGen *= step( lLightDistPow2, uLightRange_FallOff_AT0_AT1[ 2 ].x ) ;

		// �o���v�}�b�v or �t�H���V�F�[�f�B���O�p�Ɍ�������ۑ�����
		#if PHONG != 0 || BUMPMAP != 0
			vLight2DirGen.w = lLightGen ;
		#endif // PHONG || BUMPMAP

	#endif // LG2_SPOT || LG2_POINT
	// �����E�X�|�b�g���C�g�����l�v�Z =========================( �I�� )




	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �J�n )
	#if BUMPMAP == 0 && PHONG == 0

		lLightLitDest.y = clamp( dot( lViewNrm, -lLightDir ), 0.0, 1.0 ) ;

		#ifdef USE_SPE

			// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
			lLightHalfVec = normalize( normalize( -lViewPos.xyz ) - lLightDir ) ;

			// lLightLitDest.z = pow( max( 0.0, N * H ), uMatPow )
			lLightLitDest.z = pow( max( 0.0, dot( lViewNrm, lLightHalfVec ) ), uMatPow ) ;

		#endif // USE_SPE

	#endif // BUMPMAP == 0 && PHONG == 0
	// �f�B�t���[�Y���C�g�ƃX�y�L�������C�g�̊p�x�����v�Z =======( �I�� )





	// �f�B�t���[�Y�J���[�v�Z =======================================( �J�n )

	#if BUMPMAP == 0 && PHONG == 0

		#if LG2_SPOT != 0 || LG2_POINT != 0

			// �f�B�t���[�Y���C�g�~�ϒl += �����E�X�|�b�g���C�g�p�x�����l * ( �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� )
			lTotalDif.xyz += lLightGen * ( lLightLitDest.y * uLightDif[ 2 ] * lDifColor.xyz + uLightAmb[ 2 ].xyz ) ;

		#else  // LG2_SPOT || LG2_POINT

			// �f�B�t���[�Y���C�g�~�ϒl += �f�B�t���[�Y�p�x�����v�Z���� * �f�B�t���[�Y�J���[ * ���C�g�̃f�B�t���[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
			lTotalDif.xyz += lLightLitDest.y * uLightDif[ 2 ] * lDifColor.xyz + uLightAmb[ 2 ].xyz ;

		#endif // LG2_SPOT || LG2_POINT

	#endif // BUMPMAP == 0 && PHONG == 0

	// �f�B�t���[�Y�J���[�v�Z =======================================( �I�� )





	// �X�y�L�����J���[�v�Z =======================================( �J�n )

	#ifdef USE_SPE

		#if BUMPMAP == 0 && PHONG == 0

			#if LG2_SPOT != 0 || LG2_POINT != 0

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * �����E�X�|�b�g���C�g���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightGen * lLightLitDest.z * uLightSpc[ 2 ] ;

			#else	// LG2_SPOT || LG2_POINT

				// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * ���C�g�̃X�y�L�����J���[
				lTotalSpc.xyz += lLightLitDest.z * uLightSpc[ 2 ] ;

			#endif	// LG2_SPOT || LG2_POINT

		#endif // BUMPMAP == 0 && PHONG == 0

	#endif // USE_SPE

	// �X�y�L�����J���[�v�Z =======================================( �I�� )




#endif  // LG2_USE
// ���C�g2�̏��� ***********************************************************************************************************************************( �I�� )















		// �S�Ẵf�B�t���[�Y�v�f�����킹�ďo�̓��W�X�^�ɃZ�b�g =====( �J�n )

		#if BUMPMAP == 0 && PHONG == 0

			// �o�̓f�B�t���[�Y�J���[ = ���C�g�f�B�t���[�Y�J���[�~�ϒl + ( �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z�������� )
			vDif = lTotalDif + uAmb_Emi ;

			// �A���t�@�̓f�B�t���[�Y�J���[�̃A���t�@�����̂܂܎g��
			vDif.w = lDifColor.w ;

		#endif // BUMPMAP == 0 && PHONG == 0

		// �S�Ẵf�B�t���[�Y�v�f�����킹�ďo�̓��W�X�^�ɃZ�b�g =====( �I�� )





		// �S�ẴX�y�L�����v�f�����킹�ďo�̓��W�X�^�ɃZ�b�g =====( �J�n )

		#if USE_SPE != 0 && BUMPMAP == 0 && PHONG == 0

			// �o�̓X�y�L�����J���[ = ���C�g�X�y�L�����J���[�~�ϒl * �X�y�L�����J���[
			vSpc = lTotalSpc * lSpeColor ;

		#endif // USE_SPE && BUMPMAP == 0 && PHONG == 0

		// �S�ẴX�y�L�����v�f�����킹�ďo�̓��W�X�^�ɃZ�b�g =====( �I�� )






	#endif // LG_USE
	// ���C�g�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )















	// �t�H�O�v�Z =============================================( �J�n )

	#if FOG_LINEAR != 0 || FOG_EXP != 0 || FOG_EXP2 != 0

		#ifdef FOG_LINEAR

			// ���`�t�H�O�v�Z
			vNrmFog.w = lViewPos.z * uFog.y + uFog.x ;

		#endif

		#ifdef FOG_EXP

			// �w���t�H�O�v�Z 1.0 / pow( e, ���� * density )
			vNrmFog.w = 1.0 / pow( abs( uFog.w ), lViewPos.z * uFog.z ) ;

		#endif

		#ifdef FOG_EXP2

			// �w���t�H�O�Q�v�Z 1.0 / pow( e, ( ���� * density ) * ( ���� * density ) )
			vNrmFog.w = 1.0 / pow( abs( uFog.w ), ( lViewPos.z * uFog.z ) * ( lViewPos.z * uFog.z ) ) ;

		#endif

	#endif // FOG_LINEAR || FOG_EXP || FOG_EXP2

	// �t�H�O�v�Z =============================================( �I�� )

#if SHADOWMAP_DRAW != 0
	// �ˉe���W���e�N�X�`�����W�Ƃ��ďo�͂��� =================( �J�n )

	vSM0Pos_SM2PosX.xyz = gl_Position.xyz ;

	// �ˉe���W���e�N�X�`�����W�Ƃ��ďo�͂��� =================( �I�� )
#endif


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
	vVtoEyeSM2PosZ.w  = dot( lWorldPos, uSMLVPMat[ 10 ] ) ;

	// �[�x�e�p�̃��C�g���猩���ˉe���W���Z�o =================( �I�� )
#endif

	// �e�N�X�`�����W�̃Z�b�g
	vTexUV0_1.x = dot( aTexUV0F4, uTexMat[ 0 ] ) ;
	vTexUV0_1.y = dot( aTexUV0F4, uTexMat[ 1 ] ) ;
	vTexUV0_1.z = dot( aTexUV1F4, uTexMat[ 2 ] ) ;
	vTexUV0_1.w = dot( aTexUV1F4, uTexMat[ 3 ] ) ;
}

