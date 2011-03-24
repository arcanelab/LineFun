#ifndef _QT_VIDEO_GRABBER_
#define _QT_VIDEO_GRABBER_

#include "ofConstants.h"
#include "ofQtUtils.h"
#include "ofUtils.h"

#define OF_QT_SAVER_CODEC_TYPE_PLANAR_RGB        0
#define OF_QT_SAVER_CODEC_TYPE_SORENSON_VIDEO    1
#define OF_QT_SAVER_CODEC_TYPE_SORENSON_VIDEO_3  2
#define OF_QT_SAVER_CODEC_TYPE_BMP               3
#define OF_QT_SAVER_CODEC_TYPE_H_264             4
#define OF_QT_SAVER_CODEC_TYPE_CINEPAK           5
#define OF_QT_SAVER_CODEC_TYPE_DV_DVCPRO_NTSC    6
#define OF_QT_SAVER_CODEC_TYPE_DV_PAL            7
#define OF_QT_SAVER_CODEC_TYPE_DVCPRO_PAL        8
#define OF_QT_SAVER_CODEC_TYPE_H_261             9
#define OF_QT_SAVER_CODEC_TYPE_H_263            10
#define OF_QT_SAVER_CODEC_TYPE_PHOTO_JPEG       11
#define OF_QT_SAVER_CODEC_TYPE_JPEG_2000        12
#define OF_QT_SAVER_CODEC_TYPE_MOTION_JPEG_A    13
#define OF_QT_SAVER_CODEC_TYPE_MOTION_JPEG_B    14
#define OF_QT_SAVER_CODEC_TYPE_MPEG4_VIDEO      15
#define OF_QT_SAVER_CODEC_TYPE_PNG              16
#define OF_QT_SAVER_CODEC_TYPE_NONE             17
#define OF_QT_SAVER_CODEC_TYPE_ANIMATION        18
#define OF_QT_SAVER_CODEC_TYPE_VIDEO            19
#define OF_QT_SAVER_CODEC_TYPE_GRAPHICS         20
#define OF_QT_SAVER_CODEC_TYPE_TGA              21
#define OF_QT_SAVER_CODEC_TYPE_TIFF             22
#define OF_QT_SAVER_CODEC_TYPE_COMPONENT_VIDEO  23

#define OF_QT_SAVER_CODEC_QUALITY_LOSSLESS		0x00000400
#define OF_QT_SAVER_CODEC_QUALITY_MAX			0x000003FF
#define OF_QT_SAVER_CODEC_QUALITY_HIGH			0x00000300
#define OF_QT_SAVER_CODEC_QUALITY_NORMAL		0x00000200
#define OF_QT_SAVER_CODEC_QUALITY_LOW			0x00000100
#define OF_QT_SAVER_CODEC_QUALITY_MIN			0x00000000

class ofQtVideoSaver{

	public :
								ofQtVideoSaver			();
		void					setup					(int width , int height , string fileName );
		void					finishMovie				();
		void					addFrame				(unsigned char* data, float frameLengthInSecs = (1/30.0f));
		void					listCodecs				();
		void					setCodecType			(int chosenCodec );
		void					setGworldPixel			(GWorldPtr gwPtr, int r, int g, int b, short x, short y);  // just for checking...

		void					setCodecQualityLevel			(int level);		// see the #defines above...

		bool					bAmSetupForRecording	() { return bSetupForRecordingMovie; }

	private:

		//-------------------------------- movie

		bool					bSetupForRecordingMovie;


		int						w;
		int						h;
	    int						codecQualityLevel;
		OSErr 					osErr;
	    short 					sResId;
	    short 					sResRefNum;
	    FSSpec 					fsSpec;
	    Movie 					movie;
	    Track 					track;
	    Media 					media;
	    string					fileName;
	    FSRef					fsref;

		// ------------------------------- frame
		Rect 					rect;
		RGBColor 				rgbColor;
		CodecType 				codecType;
		GWorldPtr 				pMovieGWorld;
		PixMapHandle 			pixMapHandle;
		Ptr 					pCompressedData;
		CGrafPtr 				pSavedPort;
		GDHandle 				hSavedDevice;
		Handle 					hCompressedData;
		long 					lMaxCompressionSize;
		ImageDescriptionHandle	hImageDescription;
};

#endif
