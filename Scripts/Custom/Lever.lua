Script.target1 = nil --entity "Target 1"
Script.target2 = nil --entity "Target 2"
Script.target3 = nil --entity "Target 3"
Script.target4 = nil --entity "Target 4"

function Script:Start()
	self.numTargets = 0
	self.entity:SetKeyValue("tag", "Lever")
	local string targetName = ""
	if self.target1~=nil then
		self.numTargets = 1
		targetName =self.target1:GetKeyValue("name")
		self.entity:SetKeyValue("target1", targetName)
	end
	if self.target2~=nil then
		self.numTargets = 2
		targetName =self.target2:GetKeyValue("name")
		self.entity:SetKeyValue("target2", targetName)
	end
	if self.target3~=nil then
		self.numTargets = 3
		targetName =self.target3:GetKeyValue("name")
		self.entity:SetKeyValue("target3", targetName)
	end
	if self.target4~=nil then
		self.numTargets = 4
		targetName =self.target4:GetKeyValue("name")
		self.entity:SetKeyValue("target4", targetName)
	end
	self.entity:SetKeyValue("numTargets", self.numTargets)
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