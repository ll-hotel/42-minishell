/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:22:18 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/16 16:27:26 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	welcome_test_subject(void)
{
	ft_putstr_fd( \
"             \033[0;34m.,-:;//;:=,\n\
         . :H@@@MM@M#H/.,+%;,\n\
      ,/X+ +M@@M@MM%=,-%HMMM@X/,\n\
     -+@MM ;$M@@MH+-,;XMMMM@MMMM@+- \n\
    ;@M@@M -XM@X/' -+XXXXXHHH@M@M#@/.\n\
  ,%MM@@MH ,@%=           .----=-=:=,.\n\
  -@#@@@MX .,              -%HX$$%%%%+;\n\
 =- \\MM@M$                  .;@MMMM@MM:\n\
 X@\\ -$MM/                    .+MM@@@M$\n\
,@M@H: :@:                    . -X#@@@@-\n\
,@@@MMX, .                    /H- ;@M@M=\n\
.H@@@@M@+,                    %MM+..%#$.\n\
 /MMMM@MMH/.                  XM@MH; -;\n\
  /%+%$XHH@$=              , .H@@@@MX,\n\
   .=--------.           -%H.,@@@@@MX,\n\
   .%MM@@@HHHXX$$$%+- .:$MMX -M@@MM%.\n\
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=\n\
       =%@M@M#@$-.=$@MM@@@M; %M%=\n\
         ,:+$+-,/H#MMMMMMM@- -,\n\
               =++%%%%+/:-.\033[0;0m\n", 1);
	ft_putstr_fd("Welcome to miniChell\n", 1);
}
