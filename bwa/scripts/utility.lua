local utility = {}

function utility.prepend(t, dir)
    for k, v in pairs(t) do
        -- Prepends 'dir' to each string in 't'
        v = dir .. v
    end
end

return utility