# genetic

## 1.robby robot introduce

This is example code for test *Complex* book.

## 2.install
```bash
# 2.1 ubuntu install 
sudo apt-get install libglfw3 libglfw3-dev libglfw3-doc
sudo apt-get  install libglew-dev

# 2.2 build
cd genetic
make

# 2.3 run
./genetic
```

## 3.TODO

Map:
- [x] display map panel.
- [x] add new map elem(OUT).
- [x] add robbie/map Selectable tab.
- [ ] display robbie and wall(Texture).
- [x] select gene & map function.
- [x] save map.
- [x] select map elem enevts.
- [x] create new map by mouse.
- [x] select save and load path.
- [ ] rebuild the Map class.
- [ ] Mapeditor history.
- [ ] redo/undo and so on.

Algorithm:
- [ ] add map/algorithm panel/tab.
- [ ] Robbie run on map.

Frame:
- [x] separate all the module from project.
- [ ] load the module by plugin.
- [x] tets for build plugin frame.
- [ ] build Window/Map/Controller/Core/base class.
- [ ] create all the windows base class.
- [ ] create the simplest module.
- [ ] modified the Makefile of whole project.
- [ ] add submodule Makefile/CmakeLists.

Target:
- [ ] run the MapEditor module.
- [ ] run the LifeGame module.
- [ ] run the genetic module.

## architecture

### core class
- [ ] biulab

- [ ] dockspace
- [ ] window
- [ ] controller

- [ ] Inspector

