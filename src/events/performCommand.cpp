#include "../browser.h"

void Browser::performCommand(BindPoint bp){
	switch(bp){
		case(NEXTTAB): nextTab(); break;
		case(PREVTAB): prevTab(); break;
		case(LASTTAB): lastTab(); break;
		case(TAB1): selectTab(0); break;
		case(TAB2): selectTab(1); break;
		case(TAB3): selectTab(2); break;
		case(TAB4): selectTab(3); break;
		case(TAB5): selectTab(4); break;
		case(TAB6): selectTab(5); break;
		case(TAB7): selectTab(6); break;
		case(TAB8): selectTab(7); break;
		case(NEXTWS): nextWorkspace(); break;
		case(PREVWS): prevWorkspace(); break;
		case(LASTWS): lastWorkspace(); break;
		case(WS1): selectWorkspace(0); break;
		case(WS2): selectWorkspace(1); break;
		case(WS3): selectWorkspace(2); break;
		case(WS4): selectWorkspace(3); break;
		case(WS5): selectWorkspace(4); break;
		case(WS6): selectWorkspace(5); break;
		case(WS7): selectWorkspace(6); break;
		case(WS8): selectWorkspace(7); break;
		case(WS9): selectWorkspace(8); break;
		case(REFRESH): refresh(); break;
		case(NEWTAB): newTab(); break;
		case(CLOSETAB): closeTab(); break;
		case(TOGGLECOMPACT): toggleCompact(); break;
		case(SETTINGS): openSettings(); break;
	}
}
