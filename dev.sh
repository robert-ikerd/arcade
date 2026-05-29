#!/bin/zsh

autoload -Uz compinit && compinit

_get_root() {
    git rev-parse --show-toplevel 2>/dev/null || echo "."
}

arcade() {
    local ROOT=$(_get_root)
    local CMD=$1
    local GAME=$2

    if [[ -z "$GAME" && ("$CMD" == "build" || "$CMD" == "play") ]]; then
        echo "❌ Error: Please specify a game name (arcade play cartpole)"
        return 1
    fi

    case "$CMD" in
        build)
            echo "--- Building $GAME ---"
            cmake --build "$ROOT/build" --target "$GAME"
            ;;
        play)
            arcade build "$GAME" && \
            echo "--- Launching $GAME ---" && \
            "$ROOT/build/games/$GAME/$GAME.app/Contents/MacOS/$GAME"
            ;;
        *)
            echo "Usage: arcade {build|play} {game_name}"
            ;;
    esac
}

_arcade_autocomplete() {
    local ROOT=$(_get_root)
    if [[ -d "$ROOT/games" ]]; then
        compadd $(ls "$ROOT/games")
    fi
}
compdef _arcade_autocomplete arcade

echo "🕹️ Arcade Tools Loaded: Use 'arcade build' or 'arcade play'"