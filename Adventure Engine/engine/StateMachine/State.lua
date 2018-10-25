local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string

State = class("State")

function State:setInput(inputVector) end
function State:handleInput() end
function State:update(dt) end
function State:render(target, states) end