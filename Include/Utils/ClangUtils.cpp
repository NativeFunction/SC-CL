#include "Utils/ClangUtils.h"
#include "Utils/Utils.h"

using namespace std;

namespace Utils {

	namespace System
	{
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation location)
		{
			int col = ClangUtils::GetColumnFromLocation(writer, location);
			cout << brightwhite << ClangUtils::GetFileFromLocation(writer, location) <<
				":" << ClangUtils::GetLineFromLocation(writer, location) << ":" << col << ": " <<
				brightred << "error: " << brightwhite << str << endl << "        " << white
				<< ClangUtils::GetLineStringFromLocation(writer, location)
				<< endl << "       ";
			for (int i = 0; i < col; i++)
			{
				cout << " ";
			}
			cout << brightyellow << "^";
			cout << white << "\r\nPress ENTER to exit..." << flush;
			cin.clear();
			cin.ignore(STREAMSIZE_MAX, '\n');
			exit(EXIT_FAILURE);
		}
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end)
		{
			clang::SourceLocation startExp = writer.getSourceMgr().getExpansionLoc(start);
			clang::SourceLocation endExp = writer.getSourceMgr().getExpansionLoc(end);
			if (startExp.getRawEncoding() > endExp.getRawEncoding())
			{
				clang::SourceLocation temp = startExp;
				startExp = endExp;
				endExp = temp;
			}
			else if (startExp.getRawEncoding() == endExp.getRawEncoding())
			{
				Throw(str, writer, start);//same position, just use default output
				return;
			}
			if (writer.getSourceMgr().getFileID(startExp).getHashValue() != writer.getSourceMgr().getFileID(endExp).getHashValue())//different files(should never happen)
			{
				Throw(str, writer, start);
				return;
			}
			else
			{
				uint32_t lineS = ClangUtils::GetLineFromLocation(writer, startExp);
				uint32_t lineE = ClangUtils::GetLineFromLocation(writer, endExp);
				uint32_t colS = ClangUtils::GetColumnFromLocation(writer, startExp);
				uint32_t colE = ClangUtils::GetColumnFromLocation(writer, endExp);
				if (lineS == lineE)
				{
					int col = ClangUtils::GetColumnFromLocation(writer, startExp);
					cout << brightwhite << ClangUtils::GetFileFromLocation(writer, startExp) <<
						":" << ClangUtils::GetLineFromLocation(writer, startExp) << ":" << col << ": " <<
						brightred << "error: " << brightwhite << str << endl << "        " << white
						<< ClangUtils::GetLineStringFromLocation(writer, startExp)
						<< endl << "       ";
					for (int i = 0; i < col; i++)
					{
						cout << " ";
					}
					cout << brightyellow << "^";
					for (uint32_t i = colS; i < colE; i++)
					{
						cout << "~";
					}
					cout << white << "\r\nPress ENTER to exit..." << flush;
					cin.clear();
					cin.ignore(STREAMSIZE_MAX, '\n');
					exit(EXIT_FAILURE);
				}
				else
				{
					string linetext = ClangUtils::GetLineStringFromLocation(writer, startExp);
					int col = ClangUtils::GetColumnFromLocation(writer, startExp);
					cout << brightwhite << ClangUtils::GetFileFromLocation(writer, startExp) <<
						":" << ClangUtils::GetLineFromLocation(writer, startExp) << ":" << col << ": " <<
						brightred << "error: " << brightwhite << str << endl << "        " << white
						<< linetext
						<< endl << "       ";
					for (int i = 0; i < col; i++)
					{
						cout << " ";
					}
					cout << brightyellow << "^";
					for (uint32_t i = colS; i < linetext.size(); i++)
					{
						cout << "~";
					}
					cout << white << "\r\nPress ENTER to exit..." << flush;
					cin.clear();
					cin.ignore(STREAMSIZE_MAX, '\n');
					exit(EXIT_FAILURE);
				}
			}
		}
		void Throw(string str, clang::Rewriter writer, clang::SourceRange range)
		{
			Throw(str, writer, range.getBegin(), range.getEnd());
		}
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation location)
		{
			int col = ClangUtils::GetColumnFromLocation(writer, location);
			cout << brightwhite << ClangUtils::GetFileFromLocation(writer, location) <<
				":" << ClangUtils::GetLineFromLocation(writer, location) << ":" << col << ": " <<
				brightblue << "warning: " << brightwhite << str << endl << "        " << white
				<< ClangUtils::GetLineStringFromLocation(writer, location)
				<< endl << "       ";
			for (int i = 0; i < col; i++)
			{
				cout << " ";
			}
			cout << brightyellow << "^" << white << endl;
		}
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end)
		{
			clang::SourceLocation startExp = writer.getSourceMgr().getExpansionLoc(start);
			clang::SourceLocation endExp = writer.getSourceMgr().getExpansionLoc(end);
			if (startExp.getRawEncoding() > endExp.getRawEncoding())
			{
				clang::SourceLocation temp = startExp;
				startExp = endExp;
				endExp = temp;
			}
			else if (startExp.getRawEncoding() == endExp.getRawEncoding())
			{
				Warn(str, writer, start);//same position, just use default output
				return;
			}
			if (writer.getSourceMgr().getFileID(startExp).getHashValue() != writer.getSourceMgr().getFileID(endExp).getHashValue())//different files(should never happen)
			{
				Warn(str, writer, start);
				return;
			}
			else
			{
				uint32_t lineS = ClangUtils::GetLineFromLocation(writer, startExp);
				uint32_t lineE = ClangUtils::GetLineFromLocation(writer, endExp);
				uint32_t colS = ClangUtils::GetColumnFromLocation(writer, startExp);
				uint32_t colE = ClangUtils::GetColumnFromLocation(writer, endExp);
				if (lineS == lineE)
				{
					int col = ClangUtils::GetColumnFromLocation(writer, startExp);
					cout << brightwhite << ClangUtils::GetFileFromLocation(writer, startExp) <<
						":" << ClangUtils::GetLineFromLocation(writer, startExp) << ":" << col << ": " <<
						brightpurple << "warning: " << brightwhite << str << endl << "        " << white
						<< ClangUtils::GetLineStringFromLocation(writer, startExp)
						<< endl << "       ";
					for (int i = 0; i < col; i++)
					{
						cout << " ";
					}
					cout << brightyellow << "^";
					for (uint32_t i = colS; i < colE; i++)
					{
						cout << "~";
					}
					cout << white << "\r\n";
				}
				else
				{
					string linetext = ClangUtils::GetLineStringFromLocation(writer, startExp);
					int col = ClangUtils::GetColumnFromLocation(writer, startExp);
					cout << brightwhite << ClangUtils::GetFileFromLocation(writer, startExp) <<
						":" << ClangUtils::GetLineFromLocation(writer, startExp) << ":" << col << ": " <<
						brightpurple << "warning: " << brightwhite << str << endl << "        " << white
						<< linetext
						<< endl << "       ";
					for (int i = 0; i < col; i++)
					{
						cout << " ";
					}
					cout << brightyellow << "^";
					for (uint32_t i = colS; i < linetext.size(); i++)
					{
						cout << "~";
					}
					cout << white << "\r\n";
				}
			}
		}
		void Warn(string str, clang::Rewriter writer, clang::SourceRange range)
		{
			Warn(str, writer, range.getBegin(), range.getEnd());
		}
	}
	namespace ClangUtils
	{
		uint32_t GetLineFromLocation(clang::Rewriter writer, clang::SourceLocation location)
		{
			return writer.getSourceMgr().getPresumedLoc(location).getLine();
		}
		uint32_t GetColumnFromLocation(clang::Rewriter writer, clang::SourceLocation location)
		{
			return writer.getSourceMgr().getPresumedLoc(location).getColumn();
		}
		string GetFileFromLocation(clang::Rewriter writer, clang::SourceLocation location)
		{
			return writer.getSourceMgr().getFilename(location).str();
		}
		string GetLineStringFromLocation(clang::Rewriter writer, clang::SourceLocation location)
		{
			uint32_t col = GetColumnFromLocation(writer, location);
			clang::SourceLocation start = location.getLocWithOffset(1 - col);
			const char* lineStart = writer.getSourceMgr().getCharacterData(start);
			int len = 0;
			while (lineStart[len] != '\n' && lineStart[len] != '\r' && lineStart[len] != '\0')
				len++;
			string line(lineStart, len);
			replace(line.begin(), line.end(), '\t', ' ');//replace tabs with spaces so ^ aligns nicely on the console
			return line;
		}

	}

}