;***********************************************************
;*      Libary: My Delays.inc                              *
;*      Contains:                                          * 
;*               Delay                                     *
;*                                                         *
;*                                                         *
;*              Author: Riley McGuire                      *
;*                                                         *
;*              Last Modified: January 15, 2018 (created)  *
;*                                                         *
;***********************************************************


;***********************************************************
;*      Delay  Subroutine                                  *
;*                                                         * 
;*      Requires:       Number of msec specified in X      *
;*      Returns:        None                               *
;*      Regs Affected:  Trashes Y                          *
;*                                                         *
;*      Description:    This performs a delay of the number*
;*                      of ms specified by the X register  *
;*                                                         *
;***********************************************************

Delay:    LDY #2665
Delay_2:  DBNE Y, Delay_2
          DBNE X, Delay
          RTS