import ComponentBase from "./ComponentBase.js"

export default class Adafruit_NeoPixel extends ComponentBase {
    #leds = []
    
    constructor(cmodule, pin, changedCallback, dataAttrSuffix = undefined) {
        super(cmodule, `Adafruit_NeoPixel/${pin}`)
        this.mapNodes('led', dataAttrSuffix, (e, attrVal) => {
            const index = parseInt(attrVal)
            
            if(index === NaN) {
                console.warn(`Nan attribute 'data-led' for element ${e} : led ignored`)
            }
            else {
                this.#leds[index] = { 
                    val: { r: 0, g: 0, b: 0, w: 0 }, 
                    node: e, 
                    cb: changedCallback 
                }
            }
        })
        console.debug(`Adafruit_NeoPixel on pin ${pin} initialized ${this.#leds.length} leds.`)
    }
    setChangedCallback(index, changedCallback) {
        if(index < 0 || index >= this.#leds.length) {
            throw new RangeError()
        }
        this.#leds[index].cb = changedCallback
    }
    setColor(index, r, g, b, w) {
        const led = this.#leds[index]
        
        led.cb(led.node, led.val = { r, g, b, w })
    }

    static OnOff(led, rgba, cssClass, threshold = 64) {
        if(!rgba || rgba.r < threshold && rgba.g < threshold && rgba.b < threshold) {
            led.classList.remove(cssClass)
        }
        else if(!led.classList.contains(cssClass)) {
            led.classList.add(cssClass)
        }
    }
}