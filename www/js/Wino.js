export default class Wino
{
    #components;
    #wino_loop;
    #io_modes = []
    #io = []

    constructor(cmodule, components) {
        this.#components = components
        this.#wino_loop  = async () => await cmodule.ccall('wino_loop' , undefined, [], [], { async: true })
        
        cmodule.Wino = this
        components.forEach(c => c.beforeSetup?.());
        cmodule.ccall('wino_setup', undefined, [])
        components.forEach(c => c.afterSetup?.());
        requestAnimationFrame(() => this.loop())
    }
    async loop() {
        this.#components.forEach(c => c.beforeLoop?.());
        await this.#wino_loop()
        this.#components.forEach(c => c.afterLoop?.());
        requestAnimationFrame(() => this.loop())
    }
    setIoMode(pin, mode) {
        this.#io_modes[pin] = mode
    }
    setIo(pin, val) {
        this.#io[pin] = val
    }
    getIo(pin) {
        return this.#io[pin] ?? 0
    }
}