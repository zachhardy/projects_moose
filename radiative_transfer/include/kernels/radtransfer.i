[Mesh]
  [mesh]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 64
    ny = 64
    xmax = 1.0
    ymax = 1.0
  []
  [blocks]
    type = ParsedSubdomainMeshGenerator
    input = mesh
    combinatorial_geometry = '(x < 7/16 & x > 3/16 & y > 9/16 & y< 13/16) |
                              (y < 7/16 & y > 3/16 & x > 9/16 & x < 13/16)'
    block_id = 1
  []
[]

[Variables]
  [temperature]
    family = lagrange
    order = first
  []
  [radiation]
    family = lagrange
    order = first
  []
[]

[AuxVariables]
  [radiation_temperature]
    family = lagrange
    order = first
  []
[]

[Materials]
  [low_z_mat]
    type = RadiativeTransferMaterial
    atomic_mass = 1.0
    temperature = temperature
    radiation = radiation
    block = 0
  []
  [high_z_mat]
    type = RadiativeTransferMaterial
    atomic_mass = 10
    temperature = temperature
    radiation = radiation
    block = 1
  []
[]

[Kernels]
  [conduction]
    type = RadiativeTransferDiffusion
    variable = temperature
    coupled_var = radiation
  []
  [diffusion]
    type = RadiativeTransferDiffusion
    variable = radiation
    coupled_var = temperature
  []
  [radiation_source]
    type = RadiativeTransferReaction
    variable = radiation
    coupled_var = temperature
  []
  [material_source]
    type = RadiativeTransferReaction
    variable = temperature
    coupled_var = radiation
  []
  [temperature_time_derivative]
    type = MassLumpedTimeDerivative
    variable = temperature
  []
  [radiation_time_derivative]
    type = MassLumpedTimeDerivative
    variable = radiation
  []
[]

[AuxKernels]
  [radiation_temperautre_kernel]
    type = ParsedAux
    variable = radiation_temperature
    args = 'radiation'
    function = 'pow(radiation, 1/4)'
  []
[]


[ICs]
  [temperature_ic]
    type = FunctionIC
    function = temperature_ic
    variable = temperature
    block = '0 1'
  []
  [radiation_ic]
    type = FunctionIC
    function = radiation_ic
    variable = radiation
    block = '0 1'
  []
[]

[BCs]
  [temperature_bc]
    type = NeumannBC
    variable = temperature
    boundary = 'right left top bottom'
    value = 0
  []
  [radiation_bc]
    type = NeumannBC
    variable = radiation
    boundary = 'right left top bottom'
    value = 0
  []
[]

[Functions]
  [temperature_ic]
    type = ParsedFunction
    value = 'pow(0.001+100*pow(e, -100*(pow(x,2)+pow(y,2))),0.25)'
  []
  [radiation_ic]
    type = ParsedFunction
    value = '0.001+100*pow(e, -100*(pow(x,2)+pow(y,2)))'
  []
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  petsc_options_iname =  '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  start_time = 0.0
  end_time = 3.0
  [TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 1e-3
    percent_change = 0.2
  []
#  [./TimeStepper]
#    type = IterationAdaptiveDT
#    dt = 5e-3
#    cutback_factor = 0.75
#    growth_factor = 1.5
#    optimal_iterations = 5
#  [../]
[]

[Outputs]
  exodus = true
[]
