;----------------------------------------------------------------------------------------
;                                     Ресурсы...
;----------------------------------------------------------------------------------------
section '.rsrc' resource data readable
        directory       RT_MENU,appMenu,\
                        RT_ICON,icons,\
                        RT_GROUP_ICON,group_icons

        resource        appMenu, 303,LANG_NEUTRAL,IDR_MAINMENU

        resource        icons,1, LANG_NEUTRAL,icon_data

        resource        group_icons,17,LANG_NEUTRAL,main_icon


        menu    IDR_MAINMENU
                menuitem        '&Mine',0,MFR_POPUP; + MFR_END
                                menuitem        '&UniMons',1,MFT_STRING
                                menuitem        '&Open',2,MFT_STRING
                                menuitem        '&Save',3,MFT_STRING
                                menuseparator
                                menuitem        '&Exit',4,MFR_END

                menuitem        '&Exted',0,MFR_POPUP
                                menuitem        '&Talk',10,MFT_STRING
                                menuitem        '&Lang',11,MFR_END
                menuitem        '&About...', 20, MFR_END



         icon main_icon,icon_data,'Icon.ico'        
