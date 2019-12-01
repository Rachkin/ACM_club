-- Sample room

function enter()
    room = {  }
    room["background"] = "front"
    room["say"]        = glob_gets(0)
    room["characters"] = {"giorno"}
    room["speaker"]    = "giorno"
    return room
end

function next(variant)
    return "sample1" -- next file is sample.lua
end