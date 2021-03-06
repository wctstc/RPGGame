

#include "FrameLoader.h"

#include "dataconfig_frame.pb.h"
#include "Platform.h"

bool FrameLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_frame.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::FRAMEArray ayFrame;
	if (!ayFrame.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayFrame.items_size(); ++i)
	{
	    Frame oFrame;
		
		oFrame.iID = (property_type)(ayFrame.items(i).id());
		oFrame.iHandle_id = (property_type)(ayFrame.items(i).handle_id());

		oFrame.sName = platform::UTF_82ASCII(ayFrame.items(i).name());
		oFrame.sDescription = platform::UTF_82ASCII(ayFrame.items(i).description());



		for (int j = 0; j < ayFrame.items(i).option_size(); ++j)
		{
			oFrame.stOption.iNotify = (int)(ayFrame.items(i).option(j).notify());
			oFrame.stOption.iFrame_id = (int)(ayFrame.items(i).option(j).frame_id());

			oFrame.stOption.sDescription = platform::UTF_82ASCII(ayFrame.items(i).option(j).description());
		}

        m_vecRecords.push_back(oFrame);
	}
}
	
const Frame *FrameLoader::GetFrameByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Frame *FrameLoader::GetFrameByHandle_id(const int iHandle_id)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iHandle_id == iHandle_id)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const Frame *FrameLoader::GetFrameByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const Frame *FrameLoader::GetFrameByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
