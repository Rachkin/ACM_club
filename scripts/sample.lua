-- Sample room

function enter()
    room = {  }
    room["background"] = "coridor1"
    room["say"]        = glob_gets(txt)
    room["characters"] = {"giorno"}
    room["speaker"]    = "giorno"
    return room
end

function next(variant)
    glob_sets(txt, "muda")
    return "sample" -- next file is sample.lua
end