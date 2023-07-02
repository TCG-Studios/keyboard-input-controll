
interface IsidenavItems {
    translation: string
    icon: string
    link: string

}

export const SidenavItems = [
    [
        {
            label: "navigation.home",
            icon: "home",
            link: "/home"
        },
    ],
    [
        {
            label: "navigation.modules",
            icon: "widgets",
            link: "/modules"
        },
        {
            label: "navigation.mapping",
            icon: "keyboard",
            link: "/bindings"
        },
    ],
    [
        {
            label: "navigation.settings",
            icon: "settings",
            link: "/settings"
        },
        {
            label: "navigation.stats",
            icon: "monitoring",
            link: "/stats"
        },
    ],
    [
        {
            label: "navigation.about",
            icon: "info",
            link: "/about"
        },
        {
            label: "navigation.help",
            icon: "help",
            link: "/help"
        },
    ]
]