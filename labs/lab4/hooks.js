Java.perform(function () {
    console.log(">>> Hooking all known Dex loading APIs and overloads...");

    // ========== DexClassLoader ==========
    const DexClassLoader = Java.use("dalvik.system.DexClassLoader");
    DexClassLoader.$init.overloads.forEach(function (overload) {
        overload.implementation = function () {
            console.log("\n[DexClassLoader]");
            for (let i = 0; i < arguments.length; i++) {
                console.log("  arg[" + i + "]: " + arguments[i]);
            }
            return overload.apply(this, arguments);
        };
    });

    // ========== PathClassLoader ==========

    // ========== DexFile.loadDex ==========
    const DexFile = Java.use("dalvik.system.DexFile");

    if (DexFile.loadDex) {
        DexFile.loadDex.overloads.forEach(function (overload) {
            overload.implementation = function () {
                console.log("\n[DexFile.loadDex]");
                for (let i = 0; i < arguments.length; i++) {
                    console.log("  arg[" + i + "]: " + arguments[i]);
                }
                return overload.apply(this, arguments);
            };
        });
    }

    // ========== DexFile constructor overloads ==========
    DexFile.$init.overloads.forEach(function (overload) {
        overload.implementation = function () {
            console.log("\n[DexFile Constructor]");
            for (let i = 0; i < arguments.length; i++) {
                console.log("  arg[" + i + "]: " + arguments[i]);
            }
            return overload.apply(this, arguments);
        };
    });

   var File = Java.use("java.io.File");
    File.delete.implementation = function () {
        console.log("[!] Blocked File.delete() on: " + this.getAbsolutePath());
        return false; // prevent deletion
    };

    try {
        var Files = Java.use("java.nio.file.Files");
        var Paths = Java.use("java.nio.file.Paths");

        Files.delete.overload("java.nio.file.Path").implementation = function (path) {
            console.log("[!] Blocked Files.delete() on: " + path.toString());
            // throw exception to simulate failure
            throw Java.use("java.nio.file.NoSuchFileException").$new(path.toString());
        };
    } catch (err) {
        console.log("[*] java.nio.file.Files not available on this API level");
    }
});
