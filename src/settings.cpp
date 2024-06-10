#include<settings.hpp>
#include<Arduino.h>


const char *iniFileName = "settings.ini";
const char *iniHeader = "HEADER";
String SSID             = "";
String PASSWORD         = "";
int nunm                = 1;

const char *bank1 = "bank1";

String bank = "";
String sample = "";
int vol = 1;


void ReadIniFile( void )
{
	LittleFS.begin();
    File fp = LittleFS.open( "/settings.ini" "r" );
	Serial.println(LittleFS.exists("/data/settings.ini"));

    if( !fp )
    {	
        Serial.println("error: SD.open");
    } else {
        Serial.println("OK: Fs.open");
    }

	//bank        = inifileString( fp, (char *)bank1, "bank", "ssid_01234" );
    //sample    = inifileString( fp, (char *)bank1, "sample", "pass_word" );
    //vol        = inifileInteger( fp, (char *)bank1, "data", 0 );

	//Serial.println(bank);
	//Serial.println(sample);
	//Serial.println(vol);
    
	LittleFS.end();
    fp.close();
};

void RoadBank(int bnum){
	File fp = LittleFS.open( iniFileName, "r" );

}


// ----------------------------------------------------------------------------
/**
 * @brief		iniファイルから文字列対応の設定値を読み出す関数
 *
 * @param[in]		File	fp			: ファイルポインタ
 * @param[in,out]	char*	header		: 取得したいキーのあるセクション
 * @param[in,out]	char*	detail		: 取得したいキー
 * @param[in,out]	char*	defaultData	: キーデータがないときのデフォルトの文字列
 *
 * @return		String	取得した文字列
 */
// ----------------------------------------------------------------------------
String inifileString( File fp,  const char *header, char *detail,  const char *defaultData)
{
	int  position, length, index = 0;

	uint8_t buf[10];
	String str	= "";
	String output = "";
	bool fFind	= false, headerHit = false;

	if( !fp ){
		return defaultData;
	}
	fp.seek( 0 );

	while ( fp.available() )
	{
		fp.read(buf, 1);
		if( !((buf[0] == 0x0d) || (buf[0] == 0x0a) ) )
		{
			str 	+= (char)buf[0];
			continue;
		}
		
		if(str != "")
		{
			if(headerHit)
			{
				if( str[0] == '[' )
				{
					String hstr = header;
					headerHit	= CheckHeadString( str, hstr);
				} else {
					String wdetail			= detail;
					if(CheckItemString(str, detail, &output) )
					{
						fFind	= true;
						break;
					}
				}
				
			} else {
				String hstr = header;
				headerHit	= CheckHeadString( str, hstr);
			}
		}
		
		str = "";
	}

	if(!fFind){output	= defaultData;}

	return output;
}


// ----------------------------------------------------------------------------
/**
 * @brief		iniファイルからintタイプの設定値を読み出す関数
 *
 * @param[in]		File	fp			: ファイルポインタ
 * @param[in,out]	char*	header		: 取得したいキーのあるセクション
 * @param[in,out]	char*	detail		: 取得したいキー
 * @param[in]		int		defaultData	: キーデータがないときのデフォルトのint
 *
 * @return		取得したint値
 */
// ----------------------------------------------------------------------------
int inifileInteger( File fp, char *header, char *detail, int defaultData )
{
	String str	= inifileString( fp, header, detail, "");
	if( str=="" )
	{
		return defaultData;
	}
	int num = str.toInt();

	return num;
}

// ----------------------------------------------------------------------------
/**
 * @brief		iniファイルからboolタイプの設定値を読み出す関数
 *
 * @param[in]		File	fp			: ファイルポインタ
 * @param[in,out]	char*	header		: 取得したいキーのあるセクション
 * @param[in,out]	char*	detail		: 取得したいキー
 * @param[in]		bool	defaultData	: キーデータがないときのデフォルトのbool値
 *
 * @return		取得したbool値
 */
// ----------------------------------------------------------------------------
bool inifileBool( File fp, char *header, char *detail, bool defaultData )
{
	String str = inifileString( fp, header, detail, "" );
	if( str == "" )
	{
		return defaultData;
	}
	int num = str.toInt();

	return ( (num==0)?true:false );
}

// ----------------------------------------------------------------------------
/**
 * @brief		セクションデータを取得する関数
 *
 * @param[in]	String	str		: セクションかどうかをチェックする文字列
 * @param[in]	String	header	: セクション文字列
 *
 * @return		bool	true:セクションを見つけた / false:セクションが見つからない
 */
// ----------------------------------------------------------------------------
bool CheckHeadString(String str, String header)
{
	bool fhead	= false;

	str.trim();
	if( str[0] == '[' )
	{
		int pos = str.indexOf("]");
		if(pos > 0)
		{
			String hstr = "";
			
			for(int i=1;i<pos;i++)
			{
				hstr	+= str[i];
			}
			
			if(hstr == header)
			{
				fhead	= true;
			} else {
				fhead	= false;
			}
		}
	}

	return fhead;
}

// ----------------------------------------------------------------------------
/**
 * @brief		キーデータから設定値を取得する関数
 *
 * @param[in]		String	str		: チェックする文字列
 * @param[in]		String	detail	: キーデータ
 * @param[in,out]	String*	Value	: 取得したデータ（文字列として取得）
 *
 * @return		bool	true:成功 / false:失敗
 */
// ----------------------------------------------------------------------------
bool CheckItemString(String str, String detail, String *Value)
{
	String item = "";
	String sub	= "";
	bool fFind	= false;
	int i;

	if(str != "")
	{
		int pos = str.indexOf("=");
		for(i=0;i<pos;i++)
		{
			sub += str[i];
		}
		sub.trim();
		
		if(sub == detail)
		{
			fFind	= true;

			int len = str.length();
			for(i=(pos+1);i<len;i++)
			{
				item	+= str[i];
			}
			item.trim();
		} else {
			fFind	= false;
		}
	}
	
	if(!fFind)
	{
		item	= "";
	}
	*Value	= item;
	
	return fFind;
}
