function Script:Start()
	self.entity:SetKeyValue("tag", "LaserGate")
end

--[[
function Script:UpdateWorld()
	
end
]]

--[[
function Script:UpdatePhysics()
	
end
]]

--[[
--This can be used to select which objects an entity collides with.  This overrides collision types completely.
function Script:Overlap(e)
	return Collision:Collide
end
]]

--[[
function Script:Collision(entity, position, normal, speed)
	
end
]]

--[[
function Script:Draw()
	
end
]]

--[[
function Script:DrawEach(camera)
	
end
]]

--[[
--This function will be called after the world is rendered, before the screen is refreshed.
--Use this to perform any 2D drawing you want the entity to display.
function Script:PostRender(context)
	
end
]]

--[[
--This function will be called when the entity is deleted.
function Script:Detach()
	
end
]]

--[[
--This function will be called when the last instance of this script is deleted.
function Script:Cleanup()
	
end
]]

--[[
--This function will be called upon completion of a one-shot animation played with the PlayAnimation() command.
function Script:EndAnimation(sequence)
	
end
]]