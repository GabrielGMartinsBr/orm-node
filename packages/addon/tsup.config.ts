import { Options } from 'tsup'

export const tsup: Options = {
    entry: ['src/index.ts'],
    format: ['cjs', 'esm'],
    dts: true,
    minify: false,
    sourcemap: true,
    splitting: false,
    clean: true,
    treeshake: true
}