-- Sample room

function enter()
    room = {  }
    room["background"] = coridor1
    room["say"]        = "O my god, Danila you shto krazy? Eto bilo greatable! Chto ti tut delaish? Privet. 1 1 1 1  11 1 1 1 1 1 1 1 1  1 1 1 1 1  1 1 1 1  1 1 1 1 1  1 1"
    room["characters"] = {neutral[sasha]}
    room["speaker"]    = name[sasha]
    return room
end

function next(variant)
    glob_sets(sasha, "muda")
    return "sample1" -- next file is sample.lua
end