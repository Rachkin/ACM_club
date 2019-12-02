-- Sample room

function enter()
    room = {  }
    room["background"] = "front"
    room["say"]        = glob_gets(GlobalVariable1)
    room["characters"] = {"giorno"}
    room["speaker"]    = "giorno"
    return room
end

function next(variant)
    glob_sets(GlobalVariable1, "muda")
    return "sample" -- next file is sample.lua
end