declare module '*.node' {
    interface Addon {
        getIndexes: (filePath: string) => string;
        getContent: (filePath: string, scriptId: number) => string;
    }
    const addon: Addon;
    export default addon;
}