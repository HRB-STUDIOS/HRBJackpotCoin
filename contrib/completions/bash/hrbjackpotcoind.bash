# bash programmable completion for hrbjackpotcoind(1) and hrbjackpotcoin-qt(1)
# Copyright (c) 2025 HRB Studios 
# HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
# Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT

_hrbjackpotcoind() {
    local cur prev words=() cword
    local hrbjackpotcoind

    # save and use original argument to invoke hrbjackpotcoind for -help
    # it might not be in $PATH
    hrbjackpotcoind="$1"

    COMPREPLY=()
    _get_comp_words_by_ref -n = cur prev words cword

    case "$cur" in
        -conf=*|-pid=*|-loadblock=*|-rpccookiefile=*|-wallet=*)
            cur="${cur#*=}"
            _filedir
            return 0
            ;;
        -datadir=*)
            cur="${cur#*=}"
            _filedir -d
            return 0
            ;;
        -*=*)	# prevent nonsense completions
            return 0
            ;;
        *)

            # only parse -help if sensible
            if [[ -z "$cur" || "$cur" =~ ^- ]]; then
                local helpopts
                helpopts=$($hrbjackpotcoind -help 2>&1 | awk '$1 ~ /^-/ { sub(/=.*/, "="); print $1 }' )
                COMPREPLY=( $( compgen -W "$helpopts" -- "$cur" ) )
            fi

            # Prevent space if an argument is desired
            if [[ $COMPREPLY == *= ]]; then
                compopt -o nospace
            fi
            return 0
            ;;
    esac
} &&
complete -F _hrbjackpotcoind hrbjackpotcoind hrbjackpotcoin-qt

# Local variables:
# mode: shell-script
# sh-basic-offset: 4
# sh-indent-comment: t
# indent-tabs-mode: nil
# End:
# ex: ts=4 sw=4 et filetype=sh
