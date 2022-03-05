/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2022  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */



#include <stdio.h>
#include <stdlib.h>

#include"../include/picsim.h"

int
main()
{
 FILE * fout;
 int i;

 fout = fopen ("modules.h", "w");

 if (fout)
  {
   fprintf(fout,"#include \"../include/picsim.h\"\n\n");
   fprintf(fout,"//dirt hack to include dynamic load in static lib\n\n");
   
   for (i = 0; i < PIC_count; i++)
    {
     fprintf (fout, " void %s_start(_pic * pic);\n", PICS[i].name);
    }
   
   fprintf(fout,"\n\nvoid dirt_load (_pic * pic)\n{\n");
   for (i = 0; i < PIC_count; i++)
    {
     fprintf (fout, " %s_start(pic);\n", PICS[i].name);
    }
   fprintf(fout,"};\n");
   
   fclose (fout);
  }
 else
  {
   printf ("Error creating modules.h\n");
  }
 return (EXIT_SUCCESS);
}

