# GameEngine
The game engine for the Studio Sim project

## Development
Currently only "officially" supports Windows - Mac and Linux support is coming soon.

### Requirements
The current state of the engine means the only available build platform currently is Window (Win32).

To setup and use the project you will need to have the following tools installed:
 - [Git](https://git-scm.com/)
 - [Premake](https://premake.github.io/) (v5)
 - [Visual Studio](https://visualstudio.microsoft.com/)

### Installation

Clone the repository and all of its dependencies
```shell
git clone --recursive https://github.com/Endor-Games/GameEngine
```
This step may take some time as it is also downloading all dependencies, some of which can be relatively large.

Setup the project using premake using the following command
```shell
premake5 vs2019
```
If there are any issue performing this step, reference the [premake wikipedia](https://github.com/premake/premake-core/wiki).

Once the project has been configured, open the `Game.sln` solution file in Visual Studio.
The solution will contain 2 projects. A project defining the engine itself, along with a second project that serves as an example project to use the engine.
