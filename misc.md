- setup glfw + glad for context/window creation and basic shader pipeline
- set an hello triangle working

- assimp to import format and assests

- mesh (vertices, uvs, normal) the skeletons(bone hierarchy) and skimming weight for jiggle physics

- skeletal animation/ skimming
- implement linear blend skinning(standard gpu skinning, pass bone matices to the vertex shader, each vertex has bone indices + weight)

- get the basic idle/rest pose skimmed correctly before adding dynamics - this is the hardest part than the physics

- the actual physics
- mass spring damper per bone: attach virtual point mass to the top of the relevant bones, connected to the bone true position

- compute target posiotn from the skeletal animation 
- applying spring fore pulling the jiggle point toward the target, plus damping, plus gravity/inertia from the parent bone velocity

- integrate the semi-implicit euler or verlet integration

- feed that into the bones local rotation/translation before skinning 

- verlet based chains: treat each jiggle bones as the particle constrained by distance constraints to its parent - simpler and more stable than spring mass, used a lot in hair/cloth (jakobian's advanced character physics)

- tuning
- parameter stiffness, damping, max angle/displacement clamp (to stop flying off) and how much of the parent bone's angular velocity gets inherited most of the feel is in clamping + damping tuning


