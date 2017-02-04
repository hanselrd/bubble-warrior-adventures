local utility = {}

function utility.prepend(t, dir)
    for i, v in ipairs(t) do
        -- Prepends 'dir' to each string in 't'
        t[i] = dir .. v
    end
end

return utility