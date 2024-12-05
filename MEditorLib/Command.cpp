// Command.cpp: implementation of the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
	m_bUndoable=FALSE;
}

CCommand::~CCommand()
{

}

void CCommand::Execute()
{

}

void CCommand::UnExecute()
{

}

BOOL CCommand::IsUndoable()
{
	return m_bUndoable;
}

int CCommand::GetCommandCount()
{
	return 0;
}

void CCommand::AddCommand(CCommand *cmd)
{

}

CString CCommand::ClassName()
{
	return _T("");
}

void CCommand::ClearContent()
{

}
