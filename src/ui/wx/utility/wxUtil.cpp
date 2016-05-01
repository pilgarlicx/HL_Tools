#include <algorithm>

#include <wx/mimetype.h>

#include "wxUtil.h"

namespace wx
{
bool CompareVideoModeResolutions( const wxVideoMode& lhs, const wxVideoMode& rhs )
{
	return lhs.GetWidth() == rhs.GetWidth() && lhs.GetHeight() == lhs.GetHeight();
}

bool GetUniqueVideoModes( const wxDisplay& display, std::vector<wxVideoMode>& videoModes, const VideoModeComparator comparator )
{
	videoModes.clear();

	const wxArrayVideoModes modes = display.GetModes();

	for( size_t uiIndex = 0; uiIndex < modes.Count(); ++uiIndex )
	{
		videoModes.push_back( modes[ uiIndex ] );
	}

	videoModes.erase( std::unique( videoModes.begin(), videoModes.end(), comparator ), videoModes.end() );

	return true;
}

bool GetUniqueVideoModes( const wxDisplay& display, std::vector<wxVideoMode>& videoModes )
{
	return GetUniqueVideoModes( display, videoModes, &CompareVideoModeResolutions );
}

wxColor ColorTowx( const Color& color )
{
	return wxColor( color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha() );
}

Color wxToColor( const wxColor& color )
{
	return Color( color.Red(), color.Green(), color.Blue(), color.Alpha() );
}

bool LaunchDefaultProgram( const wxString& szExtension, const wxString& szParameters )
{
	wxFileType* pFileType = wxTheMimeTypesManager->GetFileTypeFromExtension( szExtension );

	bool bSuccess = false;

	if( pFileType )
	{
		wxString szOpenCommand;

		if( pFileType->GetOpenCommand( &szOpenCommand, wxFileType::MessageParameters( szParameters ) ) )
		{
			bSuccess = wxExecute( szOpenCommand, wxEXEC_ASYNC ) != 0;
		}

		delete pFileType;
	}

	return bSuccess;
}

bool LaunchDefaultTextEditor( const wxString& szFilename )
{
	return LaunchDefaultProgram( "txt", szFilename );
}
}