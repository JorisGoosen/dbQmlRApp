from conan import ConanFile

class JaspConanConfig(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sqlite3/3.49.1")