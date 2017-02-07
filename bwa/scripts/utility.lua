local utility = {}

--[[
    Prepends 'dir' to every string in 't'
    Assumes that 't' is a table full of
    strings.
--]]
function utility.prepend(t, dir)
    for i, v in ipairs(t) do
        -- Prepends 'dir' to each string in 't'
        t[i] = dir .. v
    end
end

return utility
