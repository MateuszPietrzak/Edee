function CreatePluginUI()
  local self = {
    label = "Hello UI!",
    state = 0
  }

  function self:drawHeader()
    print("[Lua] Drawing header!")
  end

  function self:draw()
    self.state = self.state + 1
    print("[Lua] Draw called "..self.state.." times!")
  end

  return self
end

function OnInit(ctx)
  ctx:registerConstructor("TXT", CreatePluginUI)
end

function OnCleanup(ctx)
  print("[Lua] Cleaning up!")
end
